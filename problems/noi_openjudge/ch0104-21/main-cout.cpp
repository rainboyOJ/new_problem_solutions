#include <iostream>
int main(){
    int n,x,y;
    std::cin >> n >> x >> y;
    int ans = y / x;
    if( y % x !=0)
        ans++;
    if( n - ans <0)
        std::cout << "0";
    else
        std::cout << n-ans << "\n";
    return 0;
}
