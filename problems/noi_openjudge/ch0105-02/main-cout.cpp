#include <iomanip>
#include <iostream>

int main(){
    double t,sum = 0;
    int i;
    for(i=1;i<=12;i++){
        std::cin >> t;
        sum += t; // => sum = sum +t
    }
    std::cout << "$" << std::setw(0) << std::fixed << std::setprecision(2) << sum / 12;
    return 0;
}
