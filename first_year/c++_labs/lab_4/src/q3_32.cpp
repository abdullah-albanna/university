#include <iostream>

using namespace std;

int main(){

    double a, b;

    cout << "Enter two number separated by a space (e.g: 1 2): ";
    cin >> a >> b;

    switch(a > b){
        case true:
            cout << a << " is bigger than " << b << endl;
            break;
        case false:
            cout << b << " is bigger than " << a << endl;
            break;
    }
}