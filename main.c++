#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>
#include <cctype>
using namespace std;

// Function to evaluate a postfix expression
int evaluatePostfix(const string& expression) {
    stack<int> s;
    stringstream ss(expression);
    string token;

    // Loop to read each token from the expression
    while (ss >> token) {
        // Check if the token is a number
        if (isdigit(token[0])) {
            // Convert the token to an integer and push onto the stack
            s.push(token[0] - '0');
        } else if (token == "+" || token == "-" || token == "*" || token == "/") {
            // Check for sufficient elements in the stack before popping
            if (s.size() < 2) {
                throw invalid_argument("Error: Invalid expression");
            }

            // Pop two values from the stack
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();

            // Perform the operation based on the token (operator)
            int result = 0;
            switch (token[0]) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    if (b == 0) {
                        throw invalid_argument("Error: Division by zero");
                    }
                    result = a / b;
                    break;
                default:
                    throw invalid_argument("Error: Invalid operator");
            }

            // Push the result back onto the stack
            s.push(result);
        } else {
            throw invalid_argument("Error: Invalid expression");
        }
    }

    // Check if the final stack has exactly one element (the result)
    if (s.size() != 1) {
        throw invalid_argument("Error: Invalid expression");
    }

    return s.top();  // Return the result
}

int main() {
    string expression;
    cout << "Enter a postfix expression: ";
    getline(cin, expression);

    try {
        int result = evaluatePostfix(expression);
        cout << "Result: " << result << endl;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}
