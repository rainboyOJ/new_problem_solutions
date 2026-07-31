#include <iomanip>
#include <iostream>
#define pi 3.14159

int main(){
    double a;
    std::cin >> a;
    std::cout << std::setw(0) << std::fixed << std::setprecision(4) << a*2 << " ";
    std::cout << std::setw(0) << std::fixed << std::setprecision(4) << a*2*pi << " ";
    std::cout << std::setw(0) << std::fixed << std::setprecision(4) << a*a*pi;
    return 0;
}
