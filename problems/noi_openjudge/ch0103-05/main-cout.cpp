#include <iomanip>
#include <iostream>

int main(){
    int a,b;
    std::cin >> a >> b;
    std::cout << std::setw(0) << std::fixed << std::setprecision(9) << a*1.0/b << "\n";
    return 0;
}
