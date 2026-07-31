#include <iomanip>
#include <iostream>


int main(){
    int n;
    std::cin >> n;
    double sum = 0;
    int flag = 1;
    int i;
    for (i=1;i<=n;i++){
        sum += flag*1.0/i;
        flag *= -1;
    }
    std::cout << std::setw(0) << std::fixed << std::setprecision(4) << sum << "\n";

    return 0;
}
