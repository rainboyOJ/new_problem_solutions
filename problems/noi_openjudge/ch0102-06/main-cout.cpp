#include <iomanip>
#include <iostream>

int main(){
    float a;
    std::cin >> a;
    std::cout << std::setw(0) << std::fixed << std::setprecision(0) << a;
    return 0;
}
