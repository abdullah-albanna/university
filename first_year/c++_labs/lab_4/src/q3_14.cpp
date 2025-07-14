#include <iostream>

using namespace std;

int main(){

    int x, y;

    cout << "Enter two numbers separated by a space (e.g: 1 2): "; 
    cin >> x >> y;

    if (y == 0){
        cout << "The second number cannot be 0" << endl;
        return 1;
    }

    if ( x % y == 0)
        cout << x << " is the multiple of " << y << endl;

    else
        cout << x << " is not the multiple of " << y << endl;

    return 0;
}