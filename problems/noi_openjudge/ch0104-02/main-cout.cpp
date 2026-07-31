#include <iomanip>
#include <iostream>

int main(){
    double a;
    std::cin >> a;
    if( a < 0)
        a = -a;
    std::cout << std::setw(0) << std::fixed << std::setprecision(2) << a;
    return 0;
}
