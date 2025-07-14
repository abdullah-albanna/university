#include <iostream>
#include <string>

using namespace std;

int main(){

    int age;
    string age_group;

    cout << "Enter your age: ";
    cin >> age;

    if (age <= 0){
        cout << "You cannot be 0 or below :(" << endl;
        return 1;
    }

    if (age >= 1 && age <= 18)
        age_group = "a child";
    
    else if (age >= 19 && age <= 25)
        age_group = "young";
        
    else
        age_group = "old";
    
    cout << "You are " << age_group << endl;
}