#include <iostream>

using namespace std;

int main() {

    int x, y;

    cout << "Enter two numbers separated by a space (e.g: 1 2): ";
    cin >> x >> y;

    if (x == y)
        cout << x << " and " << y << " are the same values" << endl;

    else if (x > y)
        cout << x << " is bigger than " << y << endl;
    else
        cout << y << " is bigger than " << x << endl;
}