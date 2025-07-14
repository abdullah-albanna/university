#include <iostream>

using namespace std;

bool canFormSquare(const int a, const int b, const int c, const int d) {
    return (a == b) && (b == c) && (c == d);
}

int main(){

    int a, b, c, d;

    cout << "Enter the angles for the square (e.g: 4 4 4 4): ";
    cin >> a >> b >> c >> d;

    if (canFormSquare(a, b, c , d))
        cout << "Angle is valid to form a square" << endl;
    else
        cout << "Angle cannot form a square" << endl;
}