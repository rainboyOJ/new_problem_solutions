#include <iomanip>
#include <iostream>

int main(){
    double a;
    int n;
    int i;
    std::cin >> a;
    std::cin >> n;
    for (i=1;i<=n;i++){
        a = a*1.001;
    }
    std::cout << std::setw(0) << std::fixed << std::setprecision(4) << a;
    return 0;
}
