#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int applyOperation(int a, char op, int b) {
    switch (op) {

    case '+':
        return a + b;
    case '-':
        return a - b;
    }

    return 0;
}

bool hasDigit(const string& str) {
    for (auto ch : str) {
        if (isdigit(ch)) {
            return true;
        }
    }
    return false;
}

int main() {

    string equation;
    char op;

    int a = 0, b = 0, c = 0;
    int x1 = 0, x2 = 0, delta;

    int result1 = 0, result2 = 0;

    vector<char> operations;

    char last_sign = '+';

    int ax1, bx1, ax2, bx2;

    string current_value;

    int position = 1;

    cout << "Example: 2x^2 + 3x + 1 = 0" << endl;

    cout << "Enter the equation: ";
    getline(cin, equation);

    for (auto ch : equation) {

        if (ch == ' ' || ch == '^')
            continue;

        if (ch == '+' || ch == '-' || ch == '=') {

            // TODO gets the sign after of the number, handle that to be the previous
            if (ch == '+' || ch == '-') {
                operations.push_back(ch);
                last_sign = ch; // tracks if it's + or - so we can assign it to
                                // the number
            }

            if (position == 1)
                hasDigit(current_value) ? a = (last_sign == '+')
                                                  ? stoi(current_value)
                                                  : -stoi(current_value)
                                        : a = 1;

            else if (position == 2)
                hasDigit(current_value) ? b = (last_sign == '+')
                                                  ? stoi(current_value)
                                                  : -stoi(current_value)
                                        : b = 1;

            else if (position == 3)
                hasDigit(current_value) ? c = (last_sign == '+')
                                                  ? stoi(current_value)
                                                  : -stoi(current_value)
                                        : c = 1;

            current_value.clear();
            position++;

        } else
            current_value += ch;
    }

    cout << "Parsed values: a = " << a << ", b = " << b << ", c = " << c
         << endl;

    delta = pow(b, 2.0) - 4 * a * c;

    cout << "Delta: " << delta << endl;

    if (delta > 0) {

        x1 = (-b + sqrt(delta)) / (2 * a);
        x2 = (-b - sqrt(delta)) / (2 * a);

        cout << "Roots: x1= " << x1 << ", x2= " << x2 << endl;
    }

    else if (delta == 0) {
        x1 = -b / (2 * a);
        cout << "Single root: x = " << x1 << endl;
    }

    else if (delta < 0) {

        cout << "There is no solution" << endl;
        return 1;
    }

    ax1 = a * pow(x1, 2.0);
    bx1 = b * x1;
    result1 = applyOperation(applyOperation(ax1, operations[0], bx1),
                             operations[1], c);

    ax2 = a * pow(x2, 2.0);
    bx2 = b * x2;
    result2 = applyOperation(applyOperation(ax2, operations[0], bx2),
                             operations[1], c);

    cout << "Result with x1: " << result1 << endl;
    cout << "Result with x2: " << result2 << endl;

    if (result1 == 0)
        cout << "The correct value for x is x1" << endl;
    else if (result2 == 0)
        cout << "The correct value for x is x2" << endl;
    else
        cout << "No correct solution found." << endl;

    return 0;
}
