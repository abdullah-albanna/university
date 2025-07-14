#include <iostream>

#define VOWELS "AEIOUaeiou"

using namespace std;

bool isVowel(const char ch) { return string(VOWELS).find(ch) != string::npos; }

int getVowels(const string str) {
    int vowel_counter = 0;

    for (char ch : str) {
        if (isVowel(ch))
            vowel_counter++;
    }

    return vowel_counter;
}


int main() {

    string text;
    int vowels = 0;

    cout << "Enter text to check: ";
    getline(cin, text);

    vowels = getVowels(text);

    cout << "Number of Vowels: " << vowels
         << "\nNumber of Consonant: " << (text.length() - vowels) << endl;
}