/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-17 17:10:30
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

ll n,m;
ll ans;

ll get_phi(ll n) {
    ll res = n;

    // 求所有的因子
    for(ll i = 2;i * i <= n ; ++i)
    {
        if( n % i == 0) {

            // 公式：res = res * (1 - 1/p) => res = res / p * (p - 1)  
            res = res / i *(i-1);


            //去除质因子
            while( n % i == 0) n /= i;
        }

    }
    // 处理剩余的大质数因子
    if( n > 1) res = res / n * (n-1);

    return res;
}



signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    std::cin >> n;


    for(ll i = 1 ;i*i <= n; i++) {
        if( n % i == 0) {
            // i 是d的因子
            ans += i * get_phi(n/i);

            // 不能重复的计算
            if( i *i != n) {
                ans += (n /i) * get_phi(i);
            }
        }
    }

    std::cout << ans << "\n";
    
    return 0;
}
