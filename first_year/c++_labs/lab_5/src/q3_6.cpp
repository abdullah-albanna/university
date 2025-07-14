#include <iostream>
using namespace std;

bool isPrime(int num) {
    if (num <= 1)
        return false; // 0 and 1 are not prime
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return false; 
    }
    return true;
}

int main() {
    int start, end;

    cout << "Enter the start of the range: ";
    cin >> start;
    cout << "Enter the end of the range: ";
    cin >> end;

    cout << "Prime numbers between " << start << " and " << end << " are:\n";

    for (int num = start; num <= end; num++) {
        if (isPrime(num)) {
            cout << num << " ";
        }
    }
    cout << endl;
    return 0;
}
