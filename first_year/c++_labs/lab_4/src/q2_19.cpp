#include <iostream>

using namespace std;

int main(){

    int a;

    cin >> a;
    if (a > 0)
        switch (a) {
            case 1:
                a = a + 3;
            case 3:
                a++;
                break;
            case 6:
                a = a + 6;
            case 8:
                a = a * 8;
                break;
            default:
                a--;
        }
    else
        a = a + 2;
}