#include <iostream>

using namespace std;

int main() {

    int a, b;

    cout << "Enter two numbers separated by a space (e.g: 1 2): ";
    cin >> a >> b;

    if (a == b)
        cout << "They are equal" << endl;
    else
        cout << "They aren't equal" << endl;

    switch ( a == b){
        case true:
            cout << "They are equal" << endl;
            break;
        case false:
            cout << "They aren't equal" << endl;
            break;
    }
}