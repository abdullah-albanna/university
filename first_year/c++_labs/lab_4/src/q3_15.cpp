#include <iostream>
#include <string>

using namespace std;

bool isNumber(const string str){
    for (char ch : str){
        if (!isdigit(ch))
            return false;
    }

    return true;
}

bool isChar(const string str){
    if (str.length() == 1 && isalpha(str[0]))
        return true;
    else
        return false;
}

int main(){

    string input;

start:

    cout << "Enter a value (char, number, sign): ";
    cin >> input;

    if (input[0] == '-' || input[0] == '+')
        cout << "That's a sign" << endl;

    else if (isNumber(input))
        cout << "That's numbers" << endl;
    
    else if (isChar(input))
        cout << "That a char" << endl;

    else{
        cout << "That's not valid, try again" << endl;
        goto start;
    }
}