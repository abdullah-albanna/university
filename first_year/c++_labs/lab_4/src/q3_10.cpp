#include <iostream>

using namespace std;

int main(){

    double x, y;
    char op;    

    cout << "Enter first number: ";
    cin >> x;

    cout << "Enter second number: ";
    cin >> y;

    cout << "Enter the operation: ";
    cin >> op;

    cout << endl;

    if (op == '+')
        cout << x << op << y << " = " << x + y << endl;
    else if (op == '-')
        cout << x << op << y << " = " << x - y << endl;
    else if (op == '*')
        cout << x << op << y << " = " << x * y << endl;
    else
        cout << "Unknown operation sign" << endl;

    
    switch (op){
        case '+':
            cout << x << op << y << " = " << x + y << endl;
            break;
        
        case '-':
            cout << x << op << y << " = " << x - y << endl;
            break;
        
        case '*':
            cout << x << op << y << " = " << x * y << endl;
            break;
        
        default:
            cout << "Unknown operation" << endl;
    }

    return 0;
}