#include <iostream>

using namespace std;

int main(){

    // inputs are 10 30 16 25 76 -1

    int num = 0;
    int sum;
    int count = 0;
    
    cin >> sum; // 10

    while (count < 3){
        cin >> num;  // 30, 16, 25, 
        sum = sum + num; // 40, 56, 81
        count++; // 1, 2, 3
    }

    cout << "Sum = " << sum << endl; // 81
}