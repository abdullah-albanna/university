#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {

    string text;
    string text_rev;

    cout << "Enter the value: ";
    cin >> text;

    text_rev = text;

    reverse(text_rev.begin(), text_rev.end());

    if (text_rev == text)
        cout << "Valid Palindrome" << endl;
    else
        cout << "Invalid Palindrome" << endl;
}