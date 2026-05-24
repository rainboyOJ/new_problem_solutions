//非常暴力的算法
#include <bits/stdc++.h>
using namespace std;



//是否 y只有因子2 和 5
bool is_only_25(int y) {
    while( y % 2 == 0) y /=2;
    while( y % 5 == 0) y /=5;
    return y == 1;
}

int get_k(int y) {
    while( y % 2 == 0) y /=2;
    while( y % 5 == 0) y /=5;
    return y;
} 

int main () {
    int n;
    std::cin >> n;
    int ans = 0;
    for(int y = 1;y <= n ;++y ) // y: 1->n
    {
        int k = get_k(y);
        if( k == 0) continue;
        ans += n / k;
    }
    std::cout << ans << "\n";
    
    return 0;
}
