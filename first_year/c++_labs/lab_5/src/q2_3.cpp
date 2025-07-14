#include <iostream>

using namespace std;

int main(){
    // input are 25 36 18 16 -1

    int num;
    int sum;

    cin >> sum; // 25
    num = sum;
    
    while (num != -1){
        cin >> num; // 36, 18, 16, -1
        sum = sum + num; // 61, 79, 95, 94
    }

    cout << "Sum = " << sum << endl; // 94

}