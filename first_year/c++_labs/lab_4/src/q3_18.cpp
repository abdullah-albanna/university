#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Employee {
    string name;
    double hoursWorked;
    double hourlyRate;
    double grossPay;
};

double calcGrossPay(const double hrs_w, const double hrs_r) {

    double pay = hrs_w * hrs_r;

    if (hrs_w > 40)
        return pay * 1.5;

    return pay;
}

int main() {
    vector<Employee> employees;

    int number_of_employees;

    string name;
    double hours_worked, hourly_rate;

    cout << "How many employees are there (e.g: 5): ";
    cin >> number_of_employees;
    cin.ignore();

    cout << endl;

    for (int i = 1; i <= number_of_employees; i++) {

        cout << "Enter employee name: ";
        getline(cin, name);

        cout << "Enter the amount of hours worked (e.g: 20): ";
        cin >> hours_worked;

        cout << "Enter the amount of hourly rate (e.g: 13.93): ";
        cin >> hourly_rate;

        cout << endl;

        cin.ignore();

        employees.push_back(Employee{
            name : name,
            hoursWorked : hours_worked,
            hourlyRate : hourly_rate,
            grossPay : calcGrossPay(hours_worked, hourly_rate)
        });
    }

    cout << endl;

    for (const Employee employee : employees) {
        cout << "Employee: " << employee.name << endl;
        cout << "Hours Worked: " << employee.hoursWorked << endl;
        cout << "Hourly Rate: $" << employee.hourlyRate << endl;
        cout << "Gross Pay: $" << employee.grossPay << endl;

        cout << endl;
    }
}