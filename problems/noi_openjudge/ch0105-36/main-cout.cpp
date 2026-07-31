#include <iomanip>
#include <iostream>


int main(){
    double x;
    int n;
    std::cin >> x;
    std::cin >> n;
    double t =1;
    double ans = 1;
    int i;
    for (i=1;i<=n;i++){
        t *=x;
        ans += t;
    }
    std::cout << std::fixed << std::setprecision(2) << ans << "\n";
    return 0;
}
