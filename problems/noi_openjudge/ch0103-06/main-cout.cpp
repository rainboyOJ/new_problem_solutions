#include <iomanip>
#include <iostream>

int main(){
    int a,b,c;
    std::cin >> a >> b;
    std::cout << std::setw(0) << std::fixed << std::setprecision(3) << b*100.0/a << "%";
    return 0;
}
