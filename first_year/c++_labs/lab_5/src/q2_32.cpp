#include <iostream>
using namespace std;

int main(){
    int a, b, c, d;
    int j;

    cin >> a >> b >> c;
    for (j = 1; j < a; j++){
        d = b + c;
        b = c;
        c = d;
        cout << c << " ";
    }
    cout << endl;
}