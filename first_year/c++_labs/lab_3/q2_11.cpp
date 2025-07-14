#include <iostream>
using namespace std;

const int NUM = 10;
const double X = 20.5;

int main(){
    
    // Entered numbers are 15 20

    int a, b;
    double z;
    char grade;

    a = 25;
    cout << "a = " << a << endl; // a = 25

    cout << "Enter Two Integers: ";
    cin >> a >> b; // a is 15, b is 20

    cout << endl;

    // The number you entered are 15 and 20
    cout << "The numbers you entered are " << a << " and " << b << endl;
    

    z = X + 2 * a - b;
    
    cout << "z = " << z << endl; // z = 30.5

    grade = 'A';

    cout << "Your grade is " << grade << endl; // Your grade is A

    a = 2 * NUM + z;

    cout << "The value of a = " << a << endl; // The value of a = 50

    return 0;
}