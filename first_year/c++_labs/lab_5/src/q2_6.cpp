#include <iostream>
using namespace std;
int main() {
    int count = 1;
    int sum = 0;
    int num;

    while (count <= 20) {
        cin >> num;

        sum += num;
        count++;
    }

    cout << sum << endl;
}