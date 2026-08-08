/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-01 09:16:32
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
const int mod = 9901;
int n,m;
ll a,b;

//快速幂
ll quick_pow(ll base,ll exp) {
    ll res = 1;

    for(  ; exp ; exp >>= 1 )
    {
        //是1就乘
        if( exp & 1) res = (res * base ) % mod;

        // base 增增
        base = (base * base) %mod;
    }
    return res;
}



// 计算等比数列前 n+1 项和: 1 + p + ... + p^n
// 公式: (p^(n+1) - 1) / (p - 1)
ll _sum(ll p, ll n) {
    if( (p % mod) == 1 ) {
        return (n+1) % mod;
    }

    ll num = (quick_pow(p,n+1) - 1 +mod) %mod;
    ll fen_mu = (p-1) %mod;

    //求逆元
    ll inv = quick_pow(fen_mu, mod-2);
    return (num * inv) % mod;
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    std::cin >> a >> b;
    if( a == 0) 
    {
        std::cout << 0 << "\n";
        return 0;
    }

    if (b== 0) {
        std::cout << 1 << "\n";
        return 0;
    }

    ll ans = 1;

    // 分解质因数
    for(int i = 2 ; i*i <= a; ++i)
    {
        if( a % i == 0) 
        {
            ll cnt = 0;
            while( a % i == 0) cnt++ ,a /=i;

            // 我们需要计算 1 + p + ... + p^(count*B)
            ll sum_ans = _sum(i, cnt * b);

            ans *= sum_ans;
            ans %= mod;

        }
    }

    //剩余部分
    if( a > 1) {
        ll sum_ans = _sum(a, b);
        ans *= sum_ans;
        ans %= mod;
    }
    
    std::cout << ans << "\n";
    return 0;
}
