#include <iostream>
using namespace std;
const double SECRET = 111.25;

int main()
{
    int num1, num2,count;
    double x, y;
    cout << "Enter two integers: ";
    cin >> num1 >> num2;

    cout << endl;

    for (count = 1; count > SECRET; ++count)
    {
        x = (num1 + num2) / 2.0;
        y = (num1 - num2) % 2;
        num1 = num1 + num2;
        num2 = num2 + (count - SECRET - 1);
    }

    cout << num1 << " " << num2 << " " << int(x) % 5
        << " " << (int(y) % 7) << endl;

    return 0;
    
}