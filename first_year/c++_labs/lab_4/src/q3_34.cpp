#include <iostream>

using namespace std;

int main(){

    int day_of_week;

    cout << "Enter the day of the week (e.g: 2): ";
    cin >> day_of_week;

    if (day_of_week == 1)
        cout << "Saturday" << endl;
    else if (day_of_week == 2)
        cout << "Sunday" << endl;
    else if (day_of_week == 3)
        cout << "Monday" << endl;
    else if (day_of_week == 4)
        cout << "Tuesday" << endl;
    else if (day_of_week == 5)
        cout << "Wednesday" << endl;
    else if (day_of_week == 6)
        cout << "Thursday" << endl;
    else if (day_of_week == 7)
        cout << "Friday" << endl;
    else
        cout << "Invalid day of week" << endl;

    
    switch (day_of_week){
        case 1:
            cout << "Saturday" << endl;
            break;
        case 2:
            cout << "Sunday" << endl;
            break;
        case 3:
            cout << "Monday" << endl;
            break;
        case 4:
            cout << "Tuesday" << endl;
            break;
        case 5:
            cout << "Wednesday" << endl;
            break;
        case 6:
            cout << "Thursday" << endl;
            break;
        case 7:
            cout << "Friday" << endl;
            break;
        default:
            cout << "Invalid day of week" << endl;
    }
}   