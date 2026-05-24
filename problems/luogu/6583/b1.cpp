//非常暴力的算法
#include <bits/stdc++.h>
using namespace std;



//是否 y只有因子2 和 5
bool is_only_25(int y) {
    while( y % 2 == 0) y /=2;
    while( y % 5 == 0) y /=5;
    return y == 1;
}

int main () {
    int n;
    std::cin >> n;
    int ans = 0;
    for(int x = 1;x <= n ;++x ) // x: 1->n
    {
        for(int y = 1;y <= n ;++y ) // y: 1->n
        {
            int d = std::gcd(x,y);
            if( is_only_25(y / d) ) {
                printf("%d / %d \n",x,y);
                ans++;
            }
        }
    }
    std::cout << ans << "\n";
    
    return 0;
}
