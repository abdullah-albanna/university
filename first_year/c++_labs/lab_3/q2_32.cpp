#include <iostream>
using namespace std;

int main(){

    int m = 66, n;

    n = ++m;

    cout << "m = " << m << ", n = " << n << endl; // m = 67, n = 67

    n = m++;

    cout << "m = " << m << ", n = " << n << endl; // m = 68, n = 67
    cout << "m = " << m++ << endl; // m = 68
    cout << "m = " << m << endl; // m = 69
    cout << "m = " << --m << endl; // m = 68

    return 0;
}