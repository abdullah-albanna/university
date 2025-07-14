#include <iostream>

using namespace std;

int main() {
    // input are 25 36 18 16 -1

    int num;
    int sum;

    cin >> num; // 25
    sum = num; // 25

    while (num != -1) {
        sum = sum + num; //50, 86, 104, 120, 
        cin >> num; // 36, 18, 16, -1
    }

    cout << "Sum = " << sum << endl; // 120
}