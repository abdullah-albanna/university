#include <iostream>
#include <string>

using namespace std;

void printInstruct() { cout << "1. low \n2. medium \n3. high" << endl; }

bool getNCheckInput(int* x) {
    cin >> *x;

    if (*x >= 1 && *x <= 3) {
        return true;
    }

    cout << endl << "Input must be 1-3" << endl;
    return false;
}

int main() {

    int a, b, c, age;

    string name, address, condition;

    cout << "_-_-_-_-_-_-_-_-_-_-_-_" << endl;
    cout << "Heat Disease Diagnosis" << endl;
    cout << "_-_-_-_-_-_-_-_-_-_-_-_" << endl << endl;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter your age: ";
    cin >> age;
    cin.ignore();

    cout << "Enter your address (e.g: 60MT Street, Sana'a, Yemen ) : ";
    getline(cin, address);

    cout << endl << endl;

    printInstruct();
    cout << "What's your " << "\033[1;31mblood\033[0m" << " pressure: ";
    if (!getNCheckInput(&a))
        return 1;

    cout << endl;

    printInstruct();
    cout << "What's your \033[1;31mheart\033[0m beat: ";
    if (!getNCheckInput(&b))
        return 1;

    cout << endl;

    printInstruct();
    cout << "What's your \033[1;36mvenous\033[0m pressure: ";
    if (!getNCheckInput(&c))
        return 1;

    if (a == 1)
        if (b == 1)

            if (c == 2)
                condition = "properly not bad";
            else
                condition = "Danger";

        else if (b == 2)

            if (c == 3)
                condition = "Danger";

            else
                condition = "properly not bad";

        else

            if (c == 2)
            condition = "properly not bad";

        else
            condition = "Danger";

    else if (a == 2)

        if (b == 2)

            condition = "Okay";

        else
            condition = "properly not bad";

    else

        if (b == 1 || b == 2)

        condition = "properly not bad";

    else

        if (c == 3)
        condition = "Dangerous";

    else
        condition = "properly not bad";

    cout << endl;

    cout << "_-_-_-_-_-_" << endl;
    cout << "   Result  " << endl;
    cout << "_-_-_-_-_-_" << endl << endl;

    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Address: " << address << endl << endl;

    cout << "Your condition is " << condition << endl;

    return 0;
}
