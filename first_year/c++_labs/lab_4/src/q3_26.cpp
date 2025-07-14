#include <iostream>

using namespace std;

bool canFormTriangle(const int a, const int b, const int c) {
    /*
    rules are
    a + b > c
    a + c > b
    b + c > a
    */
    return (a + b > c) && (a + c > b) && (b + c > a);
}

int main(){

    int a, b, c;

    cout << "Enter the angles of a triangle separated by spaces (e.g: 4 4 3): ";
    cin >> a >> b >> c;

    if (canFormTriangle(a, b, c))
        cout << "Angles are valid to form a triangle" << endl;
    else
        cout << "Angles cannot form a triangle" << endl;
    
}