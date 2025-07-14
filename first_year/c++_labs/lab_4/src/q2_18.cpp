#include <iostream>

using namespace std;

int main(){

    int beta;

    cin >> beta;
    switch (beta){
        case 3:
            beta = beta + 3;
        case 1:
            beta++;
            break;
        case 5:
            beta = beta + 5;
        case 4:
            beta = beta + 4;
    }


    cout << beta;
}