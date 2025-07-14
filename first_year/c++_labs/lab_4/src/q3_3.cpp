#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// An over-kill ? yes

int main() {
    srand(time(NULL)); // seeds the random based on the time

    int range = (rand() % 10) + 1; // so it would change the range every time, it's more fun
    int tries = (rand() % 6) + 1; // the number of tries that you get, also to make it fun

    int current_try = 0;

    int random_num = (rand() % range) + 1;

    int guessed_num;


    cout << "__________________________________" << endl;
    cout << "___________Guessing Game__________" << endl;
    cout << "__________________________________" << endl;

    cout << "The range: 1-" << range << endl;
    cout << "Your total tries: " << tries << endl;

    cout << endl;

guess:

    cout << "Enter your guess: ";
    cin >> guessed_num;

    if (guessed_num == random_num) {
        cout << "You Win!" << endl;
        return 0;
    } else {
        
        current_try++;

        if (tries > current_try) {
            cout << "You lost, try again" << endl;
            goto guess;
        }

        else {
            cout << "You lost!. You can't play anymore :(" << endl;
            return 1;
        }
    }
}