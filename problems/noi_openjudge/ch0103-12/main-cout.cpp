#include <iomanip>
#include <iostream>

#define pi 3.14

int main(){
    double r;
    std::cin >> r;
    double V = 4.0/3*pi*r*r*r;
    std::cout << std::setw(0) << std::fixed << std::setprecision(2) << V << "\n";
    return 0;
}
