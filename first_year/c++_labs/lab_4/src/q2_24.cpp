#include <iostream>
using namespace std;

int main(){

    int x = 10;
    int y = 20;
    
    if (x < 20 && y > 20){
        x = 2 * x;
        y = y / 2;

        cout << x << " " << y << " " << x - y << endl;
    }
    else {
        x = y / x;
        cout << x << " " << y << " " << x * x + y * y << endl; // 2 20 404
    }
}
