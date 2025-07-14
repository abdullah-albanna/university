#include <iostream>
using std::cout;
using std::endl; const int SECRET_NUM = 213; const double PAY_RATE = 18.35;

int main() {

    int one, two;
    double first, second, three;

    one = 18;
    two = 11;
    first = 25;
    three = first * second;

    second = 2 * SECRET_NUM;

    cout << first << "" << second << SECRET_NUM << endl;

    double paycheck = three * PAY_RATE;
    cout << "Wages = " << paycheck << endl;

    return 0;
}