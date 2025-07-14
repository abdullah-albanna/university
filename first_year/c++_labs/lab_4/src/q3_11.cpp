#include <iostream>

using namespace std;

int main(){

    int blood_vol;

    cout << "Enter your blood volume: ";
    cin >> blood_vol;

    if (4 <= blood_vol && 6 >= blood_vol)
        cout << "That's good" << endl;
    else
        cout << "You should go to the hospital" << endl;

    return 0;
}