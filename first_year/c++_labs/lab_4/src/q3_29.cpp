#include <iostream>

using namespace std;

int main(){

    double x, y;
    char op;

    cout << "Enter the equation (e.g: 1 + 2): ";
    cin >> x >> op >> y;

    switch (op){
        case '-':
            cout << x << op << y << " = " << x - y << endl;
            break;
        case '+':
            cout << x << op << y << " = " << x + y << endl;
            break;
        case '/':
            cout << x << op << y << " = " << x / y << endl;
            break;
        case '*':
            cout << x << op << y << " = " << x * y << endl;
            break;
        default:
            cout << "Invalid operation sign, valid operation: - + / *" << endl;
    }
}