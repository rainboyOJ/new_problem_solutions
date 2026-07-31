#include <iostream>

int a,b;
char c;

void init(){
    std::cin >> a;

    while(1){
        std::cin >> std::noskipws >> c;
        if( c != ' ')
            break;
    }

    std::cin >> b;
}

int suan(int a,int b,char c){
    if( c == '/')
        return a /b;
    if( c == '%')
        return a % b;
    if( c == '*')
        return a * b;
    if( c == '+')
        return a + b;
    if( c == '-')
        return a - b;
}

int main(){
    init();
    int ans = suan(a,b,c);
    std::cout << ans << "\n";

    return 0;
}
