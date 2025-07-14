#include <iostream>

using namespace std;

int getLargest(const int a, const int b) {
    if (a > b)
        return a;
    else
        return b;
}

int getSmallest(const int a, const int b) {
    if (a < b)
        return a;
    else
        return b;
}

int main() {

    int a, b, c;

    int largest, smallest;

    cout << "Enter three numbers separated by a space (e.g 1 2 3): ";
    cin >> a >> b >> c;

    largest = getLargest(getLargest(a, b), c);

    smallest = getSmallest(getSmallest(a, b), c);

    cout << "Largest number: " << largest << endl;
    cout << "Smallest number: " << smallest << endl;

    return 0;
}