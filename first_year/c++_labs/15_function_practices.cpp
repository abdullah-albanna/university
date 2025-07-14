#include <iostream>
#include <string>

using namespace std;

void welocome_me(string name);
int add(int a, int b);
void print_marks();
string get_temp();
void print_student_info();
void check_my_age();
bool is_having_anemia();
bool is_small(char);
void print_odds();
void sum_from_user();
void multi_table();
int get_max();
void login();
void swap_vals();
char get_ascii_from_int(int);

int main() {
  // string name = "Abdullah";
  // welocome_me(name);

  // print_student_info();

  // cout << add(1, 2) << endl;
  // print_marks();
  // cout << get_temp() << endl;
  // check_my_age();
  // cout << boolalpha << endl;
  // cout << (is_having_anemia() ? "You have anemia" : "You are good") << endl;
  // cout << "a is " << (is_small('a') ? "small" : "capital") << endl;
  // print_odds();
  // sum_from_user();
  // multi_table();
  // cout << "The biggest number is: " << get_max() << endl;
  // login();
  // swap_vals();
  // cout << get_ascii_from_int(65) << endl;
}

char get_ascii_from_int(int num) { return static_cast<char>(num); }

void swap_vals() {
  int a = 10;
  int b = 20;

  cout << "(a, b) before = (" << a << ", " << b << ")" << endl;

  a = a + b; // a now holds both 10 and 20
  b = a - b; // we can get the b value by subtracting a (30) - b (20) = 10 (b)
  a = a - b; // here we get the a by subtracting also a (30) - b (10; b changed
             // due to the above statement) = 20 (a)

  cout << "(a, b) before = (" << a << ", " << b << ")" << endl;
}

void login() {
  string username, password;

  for (int i = 1; i <= 3; i++) {
    cout << "Enter the username: ";
    cin >> username;

    cout << "Enter the password: ";
    cin >> password;

    if (username == "C++" && password == "Level1") {
      cout << "Logged in!" << endl;
      break;
    }
    if (i == 3)
      cout << "incorrect, get out" << endl;
    else
      cout << "incorrect, try again" << endl;
  }
}

int get_max() {
  int count;

  cout << "Enter the times that you will be entering: ";
  cin >> count;

  int nums[count], max = 0;

  for (int i = 1; i <= count; i++) {

    cout << "Enter the " << i << " number: ";
    cin >> nums[i];
    int current_value = nums[i];

    if (current_value > max) {
      max = current_value;
    }
  }
  return max;
}

void multi_table() {
  int num;

  cout
      << "Enter the number that you would like to get the multiply table for: ";
  cin >> num;

  for (int i = 1; i <= 10; i++) {
    cout << num << " * " << i << " = " << num * i << endl;
  }
}

void sum_from_user() {
  int count;

  cout << "Enter the times that you will be entering: ";
  cin >> count;

  int nums[count], sum = 0;

  for (int i = 1; i <= count; i++) {
    cout << "Enter the " << i << " number: ";
    cin >> nums[i];
    sum += nums[i];
  }

  cout << "The total sum: " << sum << endl;
}

void print_odds() {
  for (int i = 1; i <= 35; i += 2) {
    cout << "odd number: " << i << endl;
  }
}

bool is_small(char ch) {
  if (islower(ch))
    return true;
  else
    return false;
}

bool is_having_anemia() {
  double blood;

  cout << "How much blood do you have: ";
  cin >> blood;

  if (blood >= 20)
    return false; // I have no idea
  else
    return true;
}

void check_my_age() {
  int age;

  cout << "Enter your age: ";
  cin >> age;

  if (age >= 70)
    cout << "You are old" << endl;
  else if (age >= 20)
    cout << "You are young" << endl;
  else
    cout << "You are a child" << endl;
}
void welocome_me(string name) { cout << "Welcome " << name << endl; }

int add(int a, int b) { return a + b; }

void print_marks() {
  double marks[5], sum = 0;

  for (int i = 0; i <= ((sizeof(marks) / sizeof(double)) - 1); i++) {
    cout << "Enter mark" << i + 1 << ": ";
    cin >> marks[i];
    sum += marks[i];
  }

  cout << "You got " << sum << endl;
}

string get_temp() {
  double temp;

  cout << "Enter the temp: ";
  cin >> temp;

  if (temp > 73)
    return "Hot";
  else if (temp >= 12 && temp <= 73)
    return "Cool";
  else
    return "Cold";
}

void print_student_info() {
  int acadamic_id;
  string name;
  string major;
  int level;

  cout << "Enter your name ";
  cin >> name;

  cout << "Enter your acadamic id: ";
  cin >> acadamic_id;

  cout << "What's your major: ";
  cin >> major;

  cout << "And your level is? ";
  cin >> level;

  cout << "Nice, so your name is " << name << ", and your acadamic id is "
       << acadamic_id << endl
       << "and your telling me you are a " << major
       << " and been through it for " << level << " year\\s" << "?. Interesting"
       << endl;
}
