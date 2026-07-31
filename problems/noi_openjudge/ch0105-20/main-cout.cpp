#include <iomanip>
#include <iostream>
int main(){
    double h;
    std::cin >> h;
    double sum = -h;
    double fang = 0;
    int i;
    for (i=1;i<=10;i++){
        sum += 2*h;
        h = h /2;
    }
    std::cout << std::setprecision(6) << sum << "\n";
    std::cout << std::setprecision(6) << h;
    return 0;
}
