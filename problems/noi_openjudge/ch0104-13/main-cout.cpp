#include <iomanip>
#include <iostream>
int main(){
    double x;
    std::cin >> x;
    if (  x < 5){
        std::cout << std::setw(0) << std::fixed << std::setprecision(3) << -x+2.5;
    }
    else if( x < 10)
        std::cout << std::setw(0) << std::fixed << std::setprecision(3) << 2-1.5*(x-3)*(x-3);
    else 
        std::cout << std::setw(0) << std::fixed << std::setprecision(3) << x/2-1.5;
    return 0;
}
