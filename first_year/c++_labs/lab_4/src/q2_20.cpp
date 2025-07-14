#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main(){

    string str1, str2, str3;

    str1 = "English";
    str2 = "Computer Science";
    str3 = "Programming";

    cout << boolalpha;

    cout << (str1 >= str2) << endl;       // true
    cout << (str1 != "english") << endl;  // true
    cout << (str3 < str2) << endl;        // false
    cout << (str2 >= "Chemistry") << endl;// true

    if ( 'R' < '$' && '&' <= '#') cout << "$#";
            cout << "R&";
            cout << endl;
    if ('4' > '3' || 2 < -10) cout << "1 2 3 4" << endl;
        cout << "$$" << endl;
    if ("Jack" <= "John" && "Business" >= "Accounting")
        cout << "Jack Accounting" << endl;
        cout << "John Business" << endl;
        
}