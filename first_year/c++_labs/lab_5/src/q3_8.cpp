#include <iostream>
using namespace std;

void main_operation(bool& at_the_start, int& min, int& i) {
    int current_value;

    cout << "Enter the " << i << " number: ";
    cin >> current_value;

    if (at_the_start) {
        min = current_value;
        at_the_start = false;
    }

    else if (current_value < min) {
        min = current_value;
    }
    i++;
}

int get_count() {
    int count;

    cout << "How much times would be entering number: ";
    cin >> count;

    return count;
}

int with_for_loop() {
    int count = get_count();
    int min;

    bool at_the_start = true;

    for (int i = 1; i <= count;) {
        main_operation(at_the_start, min, i);
    }
    return min;
}

int with_while_loop() {
    int count = get_count();
    int min;
    int i = 1;

    bool at_the_start = true;

    while (count >= i) {
        main_operation(at_the_start, min, i);
    }

    return min;
}

int with_do_while_loop() {
    int count = get_count();
    int min;
    int i = 1;

    bool at_the_start = true;

    do {
        main_operation(at_the_start, min, i);
    } while (count >= i);

    return min;
}

int main() {
    int min = with_do_while_loop();

    cout << "The smallest number: " << min << endl;
}