#include <iostream>

using namespace std;

int main(){

    double average;

    cout << "Thanks for choosing College of Engineering" << endl;
    cout << "Enter you high school average (e.g: 91.38): ";
    cin >> average;
    
    cout << endl;

    if (average >= 80)
        cout << "Welcome" << endl;
    else
        cout << "You are not acceptable, your average is low" << endl;

    
    switch (average >= 80){
        case true:
            cout << "Welcome" << endl;
            break;
        case false:
            cout << "You are not acceptable, your average is low" << endl;
            break;
    }
}