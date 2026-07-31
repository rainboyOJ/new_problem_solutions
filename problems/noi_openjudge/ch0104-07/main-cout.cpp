#include <iostream>
#define pi 3.14159

int main(){
    int n;
    std::cin >> n;
    int a;
    std::cin >> a;
    if( n >=10 || a >=20)
        std::cout << "1";
    else {
        std::cout << "0";
    }
    return 0;
}
