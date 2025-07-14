#include <iostream> 

using namespace std;

bool canFormRectangle(const int side1, const int side2, const int side3, const int side4) {
    return (side1 == side3) && (side2 == side4);
}

int main(){

    int a, b, c ,d;

    cout << "Enter the angles for a rectangular separated by spaces (e.g: 4 2 4 2): ";
    cin >> a >> b >> c >> d;

    if (canFormRectangle(a, b, c, d))
        cout << "Angles are valid to form a rectangle" << endl;
    else
        cout << "Cannot form a rectangular from given angles" << endl;
}