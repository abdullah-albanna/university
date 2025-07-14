#include <iostream>

using namespace std;

int main(){

    char gender;

    cout << "Enter the gender character (e.g: M): ";
    cin >> gender;

    gender = toupper(gender);

    switch (gender){
        case 'F':
            cout << "Female" << endl;
            break;
        case 'M':
            cout << "Male" << endl;
            break;
        default:
            cout << "Invalid gender" << endl;
    }
}