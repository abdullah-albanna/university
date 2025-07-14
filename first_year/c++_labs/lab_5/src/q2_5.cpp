#include <iostream>

using namespace std;

int main() {
    // input are 10 -6 12 -5 -4 0 

    int num;
    int sum = 0;

    cin >> num; // 10

    while (num != 0) {

        
        
        if (num > 0)
            sum = sum + num; 
        else    
            sum = sum - num; 

        // sum: 10, 16, 28, 33, 37
        cin >> num; // -6, 12, -5, -4, 0
    }

    cout << "Sum = " << sum << endl; // 37
}