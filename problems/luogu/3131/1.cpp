/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2025-12-31 16:46:37
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const ll maxn = 2e6+5;
ll n,m;
ll a[maxn];
ll pre[maxn];
ll first[10];
ll last[10];


signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    std::cin >> n;
    for(ll i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
        pre[i] = pre[i-1] + a[i];
    }
    // 7 | a -b 
    // a \equiv b \pmod 7
    for(ll i = 0;i <= 6 ;++i ) // i: 0->6
    {
        last[i] = first[i] = -1; // 表示不存在
    }

    // 特殊判断
    first[0] = last[0] = 0;

    for(ll i = 1;i <= n ;++i ) // i: 1->n
    {
        ll mod = pre[i] % 7;
        if( first[mod] == -1) first[mod] =  i;
        last[mod] = i;
    }

    ll ans = -1;
    for(ll i = 0;i <= 6 ;++i ) // i: 0->6
    {
        ll len = last[i] - first[i];
        if( ans < len) ans = len;
    }
    std::cout << ans << "\n";

    return 0;
}
