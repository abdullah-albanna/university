#include <iostream>
using namespace std;

const int SECRET = 5;

int main(){
    int x, y, w, z;
    z = 9;

    if (z > 10){
        x = 12; 
        y = 5; 
        w = x + y + SECRET;
    }
    else {
        x = 12; 
        y = 4; 
        w = x + y + SECRET;
    }

    cout << "w = " << w << endl;
}