#include <iostream>

int main(){
    char a;
    std::cin >> std::noskipws >> a;
    int b = a;
    if( b % 2 == 0)
        std::cout << "NO";
    else
        std::cout << "YES";
    return 0;
}
