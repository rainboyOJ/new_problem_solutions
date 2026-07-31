#include <iomanip>
#include <iostream>


int main(){
    int n;
    std::cin >> n;
    double p = 1,q = 2;
    double sum = 0;
    int i;
    for (i=1;i<=n;i++){
        sum += q/p;
        double tq = q;
        q = q+p;
        p = tq;
    }
    std::cout << std::setw(0) << std::fixed << std::setprecision(4) << sum << "\n";
    return 0;
}
