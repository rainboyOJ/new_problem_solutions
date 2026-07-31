#include <iostream>

int main(){
    int a;
    std::cin >> a;
    int a1 = a % 10;
    a = a /10;
    int a2 = a % 10;
    a = a /10;
    std::cout << a1 << a2 << a;
    return 0;
}
