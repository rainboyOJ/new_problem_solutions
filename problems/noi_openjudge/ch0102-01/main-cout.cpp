#include <iostream>
/* 
 * int      4
 * double   8
 * float    4
 * bool     1
 * char     1
 *
 * sizeof
 * */

// sizeof 不是函数
// #define sizeof(int) 4
int main(){
    int a = sizeof(int);
    int b = sizeof(short);
    std::cout << a << " " << b;
    return 0;
}
