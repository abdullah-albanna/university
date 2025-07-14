#include <iostream>

using namespace std;

int main(){

    int age;

    cout << "Enter your age (e.g: 21): ";
    cin >> age;

    if (age >= 18) 
        cout << "Thank you for voting" << endl;
    else
        cout << "You cannot vote, you are not eligible to vote" << endl;
    

    switch (age >= 18){
        case true:
            cout << "Thank you for voting" << endl;
            break;
        case false:
            cout << "You cannot vote, you are not eligible to vote" << endl;
            break;
    }
}