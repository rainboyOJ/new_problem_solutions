#include <iostream>
int main(){
    int a,b;
    std::cin >> a;
    if( a == 1 || a == 3 || a == 5)
        std::cout << "NO";
    else
        std::cout << "YES";
    return 0;
}
