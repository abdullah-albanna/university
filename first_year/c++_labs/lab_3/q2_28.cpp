#include <iostream>
#include <iomanip>

using namespace std;

int main(){

    int width = 10;

    cout << left;

    cout << setw(width) << "numbers" << setw(width) << "square" << setw(width)
         << "cube" << endl;

    cout << setw(width) << 0 << setw(width) << 0 << setw(width) << 0 << endl;
    cout << setw(width) << 1 << setw(width) << 1 << setw(width) << 1 << endl;
    
    cout << endl;
    
    cout << setw(width) << 2 << setw(width) << 4 << setw(width) << 8 << endl;
    cout << setw(width) << 3 << setw(width) << 9 << setw(width) << 27 << endl;
    cout << setw(width) << 4 << setw(width) << 16 << setw(width) << 64 << endl;
    cout << setw(width) << 5 << setw(width) << 25 << setw(width) << 125 << endl;

    return 0;

}
