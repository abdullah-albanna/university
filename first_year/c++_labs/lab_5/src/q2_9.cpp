#include <iostream>
using namespace std;

int main(){
    int j, s;
    s = 0;
    for (j = 1; j <= 10; j++)
    s = s + j * (j - 1);
    /*
    0
    2
    10
    32

    */
   cout << s << endl;
}
