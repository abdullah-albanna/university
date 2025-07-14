#include <iostream>
#include <iomanip>

using namespace std;

int main(){
    char ch;

    cout << "Enter a character: ";
    cin >> ch;

    if (isupper(ch))
        cout << "Character is uppercase" << endl;
    else if (islower(ch))
        cout << "Character is lowercase" << endl;
    else
        cout << "Not a character" << endl;
    
    switch ((bool)isupper(ch)){
        case true:
            cout << "Character is uppercase" << endl;
            break;
        case false:
            switch ((bool)islower(ch)){
                case true:
                    cout << "Character is lowercase" << endl;
                    break;
                case false:
                    cout << "Not a character" << endl;
                    break;
            } break;
        default:
            cout << "?" << endl;
    }
}