#include <iostream>

using namespace std;

int main(){

    int x;

    cout << "Enter a number (e.g: 2): ";
    cin >> x;

    switch (x % 2 == 0){
        case true:
            cout << "Even" << endl;
            break;
        case false:
            cout << "Odd" << endl;
            break;
    }
}