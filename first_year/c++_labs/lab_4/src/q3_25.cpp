#include <iostream>
#include <vector>

using namespace std;

int getDays(const int month){
    int days;

    if (month == 2){
        days = 28;
        return days;
    }

    if (month == 4 || month == 6 || month == 9 || month == 11)
        days = 30;
    
    else
        days = 31;

    return days;
}

int main(){

    int month_number;

    cout << "Enter the month number (e.g: 3): ";
    cin >> month_number;

    cout << endl;

    if (month_number > 12 || month_number < 1){
        cout << "Can only be between 1-12" << endl;
        return 1;
    }

    cout << "The total days of the month: " << getDays(month_number) << endl;
}