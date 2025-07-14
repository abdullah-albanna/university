#include <iostream>

using namespace std;

int main(){

    double temp;

    cout << "Enter the temperature: ";
    cin >> temp;


    if (temp >= 73)
        cout << "Hot!" << endl;

    else if (temp >= 12 && temp <= 73)
        cout << "Cold!" << endl;
    
    else
        cout << "Cool!" << endl;
}