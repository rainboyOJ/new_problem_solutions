#include <iostream>

int main(){
    int a,b;
    char c;
    std::cin >> a >> b;
    std::cin >> std::noskipws >> c;
    std::cin >> std::noskipws >> c;
    int ans ;
    if( c == '*')
        ans = a*b;
    else if( c == '/' && b == 0){
        std::cout << "Divided by zero!";
        return 0;
    }
    else if( c == '/')
        ans = a/b;
    else if (c == '+')
        ans = a + b;
    else if (c == '-')
        ans = a - b;
    else {
        std::cout << "Invalid operator!";
        return 0;
    }
    std::cout << ans << "\n";

    return 0;
}
