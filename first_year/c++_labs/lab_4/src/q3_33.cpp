#include <iostream>

using namespace std;

void swapVarsVal(int& a, int& b) {
    a = a + b; // get both to a
    b = a - b; // get both - b = previous a
    a = a - b; // get both - b (which is a) = b
}

int main() {

    int a, b;

    cout << "Enter two values separated by a space (e.g: 1 2): ";
    cin >> a >> b;

    cout << "before" << endl;
    cout << "a = " << a << ", b = " << b << endl;

    if (!(a == b)) {
        swapVarsVal(a, b);
        
        cout << "after" << endl;
        cout << "a = " << a << ", b = " << b << endl;
    }

    swapVarsVal(a, b);

    cout << endl << "using switch" << endl;

    switch (a != b){
        case true:
            swapVarsVal(a, b);
            cout << "a = " << a << ", b = " << b << endl;
            break;
        case false:
            cout << "a = " << a << ", b = " << b << endl;
            break;
    }
}