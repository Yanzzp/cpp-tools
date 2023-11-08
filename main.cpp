#include <iostream>

using namespace std;



int main() {

    // 忘记释放指针 b 申请的内存, 从而导致内存泄露
    int *a = new int;
    int *b = new int[12];

    delete a;

    return 0;

}