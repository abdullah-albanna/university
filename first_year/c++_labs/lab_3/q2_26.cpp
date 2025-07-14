#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

const double PI = 3.14159;

int main() {

    double height, radius;

    cout << "Enter the height of the cylinder: ";
    cin >> height;

    cout << "Enter the radius of the cylinder: ";
    cin >> radius;

    cout << fixed << showpoint << setprecision(2)
         << "Volume of the cylinder = " << PI * pow(radius, 2.0) * height
         << endl;
    cout << fixed << showpoint << setprecision(2)
         << "Surface area: " << 2 * PI * pow(radius, 2.0) + 2 * PI * radius * height << endl;

    return 0;
}
