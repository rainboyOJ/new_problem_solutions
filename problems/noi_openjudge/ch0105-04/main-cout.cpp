#include <iomanip>
#include <iostream>

int main(){
    int n;
    int sum = 0;
    int i,t;
    std::cin >> n;
    for (i=1;i<=n;i++){
        std::cin >> t;
        sum +=t;
    }
    std::cout << sum << " ";
    std::cout << std::setw(0) << std::fixed << std::setprecision(5) << sum*1.0/n;
    return 0;
}
