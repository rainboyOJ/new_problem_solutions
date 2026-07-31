#include <iostream>
int main(){
    int a,b;
    std::cin >> a >> b;
    if(( a < 60 && b >= 60) || ( b < 60 && a >= 60 ))
        std::cout << "1";
    else
        std::cout << "0";
    return 0;
}
