#include <chrono>
#include <thread>
#include <iostream>
#include <string>

using namespace std;

int main() {

    cout << "\033[31m" << "STOP!" << endl;

    this_thread::sleep_for(chrono::seconds(4));

    cout << "\033[33m" << "Prepare" << endl;

    this_thread::sleep_for(chrono::seconds(2));

    cout << "\033[32m" << "GO!" << endl;

    this_thread::sleep_for(chrono::seconds(1));

    
    return 0;
}
