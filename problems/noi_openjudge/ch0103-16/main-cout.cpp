#include <cmath>
#include <iomanip>
#include <iostream>

int main(){
    double xa,ya,xb,yb;
    std::cin >> xa >> ya >> xb >> yb;
    double ans = sqrt((xa-xb)*(xa-xb)+(ya-yb)*(ya-yb));
    std::cout << std::setw(0) << std::fixed << std::setprecision(3) << ans << "\n";

    return 0;
}
