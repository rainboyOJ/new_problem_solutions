#include <iostream>
#define pi 3.14159

int main(){
    int n;
    std::cin >> n;
    if( n >=10 && n<=99)
        std::cout << "1";
    else
        std::cout << "0";
    return 0;
}
