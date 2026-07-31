#include <iomanip>
#include <iostream>
#define pi 3.14159

int main(){
    float a,b;
    std::cin >> a >> b;
    std::cout << std::setw(0) << std::fixed << std::setprecision(2) << 1/(1/a+1/b) << " ";
    return 0;
}
