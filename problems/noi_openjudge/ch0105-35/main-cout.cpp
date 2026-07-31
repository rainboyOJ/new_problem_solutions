#include <iomanip>
#include <iostream>


int main(){
    int n;
    std::cin >> n;
    double i,s = 1;
    double sum=1;
    for (i=1;i<=n;i++){
        s = s*i;
        sum += 1.0/s;
    }
    std::cout << std::setw(0) << std::fixed << std::setprecision(10) << sum << "\n";

    return 0;
}
