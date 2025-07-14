#include <iostream>
#include <math.h>

using namespace std;

void with_for_loop() {
    cout << "N\t10*N\t100*N\t1000*N" << endl;
    for (int i = 1; i <= 5; i++) {
        cout << i << "\t";
        for (int j = 1; j <= 3; j++) {
            cout << i * (pow(10, j)) << "\t";
        }
        cout << endl;
    }
}

void with_while_loop() {
    int i = 1;
    int j = 1;

    cout << "N\t10*N\t100*N\t1000*N" << endl;
    while (i <= 5) {
        j = 1;
        while (j <= 4) {
            cout << i * (pow(10, j)) << "\t";
            j++;
        }
        i++;
        cout << endl;
    }
}

void with_do_while_loop() {
    int i = 1;
    int j = 1;

    cout << "N\t10*N\t100*N\t1000*N" << endl;
    do {
        j = 1;
        do {
            cout << i * (pow(10, j)) << "\t";
            j++;
        } while (j <= 4);
        i++;
        cout << endl;
    } while (i <= 5);
}

void with_goto() {

    cout << "N\t10*N\t100*N\t1000*N" << endl;

    int i = 1;

    rows_label:
        if (i > 5)
            return;
        
        cout << i << "\t";

        int j = 1;
        columns_label:
            if (j >= 4){
                i++;
                cout << endl;
                goto rows_label;
            }

            cout << i * (pow(10, j)) << "\t";
            j++;
            goto columns_label;
}

int main() { 
    with_goto(); 
}