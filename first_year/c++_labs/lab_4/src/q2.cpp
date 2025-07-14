#include <iostream>

using namespace std;

int main(){

    int score;

    // -----------------------

    5 + 6 == 3 + 7;     // false
    2 * 6 - 4 >= 9 - 1; // true
    'U' >= 't';         // false
    'A' <= 'a';         // true
    '#' <= '+';         // true
    6.28 / 3 < 3 - 1.2; // false

    // --------------------------
    !(10 > 10);              // true
    10 <= 5 || 15 < 15;      // true
    (10 != 5) && (15 != 20); // true

    // ---------------------------
    int x = 3, y = 4, z = 7, w = 1;

    cout << "x == y: " << (x == y) << endl;
    cout << "x != z: " << (x != z) << endl;
    cout << "y == z - 3: " << (y == z - 3) << endl;
    cout << "!(z > w): " << !(z > w) << endl;
    cout << "x + y < z: " << (x + y < z) << endl;

    // ----------------------

    if (score >= 60)
        cout << "You pass." << endl;
    else
        cout << "You fail." << endl;

    //----------------------------

    char gender = 'M';
    // cout << "Enter your gender: ";
    // cin >> gender;

    switch (gender) {
    case 'M': {
        cout << "Male" << endl;
    } break;

    case 'F': {
        cout << "Female" << endl;
    } break;

    default: {
        cout << "Invalid" << endl;
    } break;
    }

    // -------------------------

    int myNum = 5;
    int yourNum = 12;

    if (yourNum % myNum == 3) {
        yourNum = 3;
        myNum = 1;
    } else if (yourNum % myNum == 2) {
        yourNum = 2;
        myNum = 2;
    } else {

        yourNum = 1;
        myNum = 3;
    }

    cout << myNum << " " << yourNum << endl;

    // -------------------

    score = 70;

    if (score == 70)
        cout << "Grade is C" << endl;
    if (score = 70)
        cout << "Grade is C" << endl;

    // ---------------------
    int n, digit;
    n = digit = 0;

    /*a.*/ switch (n <= 2) {
    case 0:
        cout << "Draw." << endl;
        break;
    case 1:
        cout << "Win." << endl;
        break;
    case 2:
        cout << "Lose." << endl;
        break;
    }

    // /*b.*/ switch (digit / 4) {
    // case 0, case 1:
    //     cout << "low." << endl;
    //     break;
    // case 1, case 2:
    //     cout << "middle." << endl;
    //     break;
    // case 3:
    //     cout << "high." << endl;
    // }

    /*c*/ switch (n % 6) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        cout << n;
        break;
    case 0:
        cout << endl;
        break;
    }

    /*d*/ switch (n % 10) {
    case 2:
    case 4:
    case 6:
    case 8:
        cout << "Even";
        break;
    case 1:
    case 3:
    case 5:
    case 7:
        cout << "Odd";
        break;
    }

    //-------------------
    int alpha {0};

    switch (alpha % 6){
        case 0: 
            alpha --;
            break;
        
        case 1: case 2:
            alpha = alpha * 2;
            break;
        case 3:
            break;
        case 4:
            alpha = alpha - 5;
        case 5:
            alpha ++;
            break;
        default:
            alpha = alpha / 3;
    }

    // -----------------------------

}