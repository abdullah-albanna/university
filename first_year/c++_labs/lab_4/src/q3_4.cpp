#include <iostream>

using namespace std;

int main(){

    double grade;

    cout << "Enter your Average grade: ";
    cin >> grade;

    if (!(grade >= 1 && grade <= 100)){
        cout << "Grade must be between 1-100" << endl;
        return 1;
    }

    cout << "\nWith for loop: " << endl;

    if (grade >= 90)
        cout << "Excellent" << endl;
    else if (grade >= 75)
        cout << "Very good" << endl;
    else if (grade >= 65)
        cout << "Good" << endl;
    else if (grade >= 50)
        cout << "Acceptable" << endl;
    else
        cout << "Failed" << endl;

    cout << "\nWith switch: " << endl;

    // I know..I know
    switch (grade >= 90){
        case true:
            cout << "Excellent" << endl;
            break;
        case false:
            switch (grade >= 75){
                case true:
                    cout << "Very good" << endl;
                    break;
                case false:
                    switch (grade >= 65){
                        case true:
                            cout << "Good" << endl;
                            break;
                        case false:
                            switch (grade >= 50){
                                case true:
                                    cout << "Acceptable" << endl;
                                    break;
                                case false:
                                    cout << "Failed" << endl;
                                    break;
                            }
                    }
            }
    }
}