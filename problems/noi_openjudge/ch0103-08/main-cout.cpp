#include <iomanip>
#include <iostream>

int main(){
    double a;
    std::cin >> a;
    std::cout << std::setw(0) << std::fixed << std::setprecision(5) << 5*(a-32)/9.0;
    return 0;
}
