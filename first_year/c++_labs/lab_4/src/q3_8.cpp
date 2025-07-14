#include <iostream>

using namespace std;

int main(){

    double height, width;

    cout << "Enter the height: ";
    cin >> height;

    cout << "Enter the width: ";
    cin >> width;

    if (height == width){
        cout << "That's a square" << endl;
    }
    else
        cout << "That's a rectangular" << endl;

    return 0;
}