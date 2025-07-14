int main() {

    int a{4};
    int b{6};
    int c;

    a = (b++) + 3;         // 9  7  0
    c = 2 * a + (++b);     // 9  8  26
    b = 2 * (++c) - (a++); // 10 45 27

    return 0;
}