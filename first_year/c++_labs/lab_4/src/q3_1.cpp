#include <iostream>

using namespace std;

int main(){

    double grade;

    cout << "Enter the grade: ";
    cin >> grade;

    if (!(grade >= 1 && grade <= 100)){
        cout << "grade must be between 1-100" << endl;
        return 1;
    }

    grade >= 50 ? cout << "pass" << endl : cout << "failed" << endl;
}