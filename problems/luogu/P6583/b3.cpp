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
    //枚举k
    for(int k = 1; k<=n;k++) {
        if( std::gcd(k,10) == 1) {
            cout << "k = " << k << endl;
            cout << "cnt x = "  ;
            for(int t = 1 ; t *k <=n;t++)
                cout << t * k << " ";
            std::cout  << "\n";

            // 枚举y
            cout << "cnt y = ";
            for(int y = 1; y <=n;y++) {
                if( y % k != 0) continue; // y里面不含有y
                if( is_only_25(y / k) == false ) continue;
                std::cout << y << " ";
                ans +=  n /k ; // ans += cnt of x
            }
            std::cout  << "\n\n";

        }
    }
    std::cout << ans << "\n";
    
    return 0;
}
