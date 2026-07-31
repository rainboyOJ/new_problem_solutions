#include <iostream>

int main(){
    int n,x,y;
    std::cin >> n >> x >> y;
    int ans = y / x;
    if( y % x != 0)
        ans++;
    std::cout << n-ans;
    return 0;
}
