/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-30 21:08:00
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
ll tot;
ll x[maxn]; // 每个元素
ll avg;
ll t[maxn]; // t[i] = x_i - avg;
ll s[maxn]; // t[i] 前缀和

ll _abs(ll t) {
    if( t < 0) t *=-1;
    return t;
}


int idx(int i) {
    return i % n;
}

void init(){
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        
        //这个id可以不要
        // 但是为了能对应解析的设定
        int id = idx(i); 

        std::cin >> x[id];
        tot+=x[id];
    }
    avg = tot / n;

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();
    for(int i = 0;i < n ;++i ) 
        t[i] = x[i] - avg;

    s[0] = t[0];
    for(int i = 1;i < n ;++i ) // i: 1->n-1
    {
        s[i] = s[i-1] + t[i];
    }

    //排列
    std::sort(s,s+n);

    // 这里为什么n-1,因为 下标从0开始了
    int k = (n-1)/2;

    ll ans = 0;
    for(int i = 0;i <= n-1 ;++i ) // i: 0->n-1
    {
        ans += _abs( s[i] - s[k]);
    }
    std::cout << ans << endl;
    
    return 0;
}
