#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
typedef long long ll;
ll mod = 19260817; 

ll read() {
    ll x = 0;
    char c = getchar();
    while (c < '0' || c >'9')  c = getchar();

    while (c >= '0' && c <= '9') {
        x = ( x * 10 + (c -'0')) % mod;
        c = getchar();
    }
    return x;
}

ll quick_pow(ll base,ll n) {
    ll res =1;
    for(ll i = n; i>0 ; i >>=1)
    {
        if( i & 1 ) {
            res *= base;
            res %= mod;
        }
        base = base *base % mod;
    }

    return res;
}

int main() {
    ll a = read();
    ll b = read();

    //  判断是否有解
    if (b == 0) {
        // 如果 b % MOD 为 0，说明 b 是 19260817 的倍数。
        // 根据题目保证 "a, b 不同时是倍数"，此时 a一定不为0。
        // 0 * x = a (mod P) 无解。
        cout << "Angry!" << endl;
    }
    else {
        // 4. 计算答案
        // 答案 = a * b的逆元 % MOD
        // b的逆元 = b^(MOD-2) % MOD (费马小定理)
        long long inv_b = quick_pow(b, mod - 2);
        long long ans = (a * inv_b) % mod;
        cout << ans << endl;
    }
    

    return 0;
}

