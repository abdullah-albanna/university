#include <iostream>

using namespace std;

int main(){

    int num;

    cout << "Enter a number to check if it's devisable by 5: ";
    cin >> num;

    num % 5 == 0 ? cout << "True" << endl : cout << "False" << endl;

    return 0;
}