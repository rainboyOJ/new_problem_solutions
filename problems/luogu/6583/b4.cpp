#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
ll n, ans=0;

// 存所有2^a x 5 ^b 组成的数字
std::vector<ll> a25;

// 求[1,v] 形如 2^a x 5 ^b 的数量
ll f(ll v) {
    return std::upper_bound(a25.begin(), a25.end(),v) - a25.begin();
}

ll g(ll n) {
    return n - n/2 - n/5 + n/10;
}

void init_a25() {
    std::vector<ll> a5;
    ll t = 1; a5.push_back(t);
    ll up = 1e12;
    for(int b = 1;b <= 17 ;++b ){
        t *=5;
        a5.push_back(t);
    }
    for(ll a = 0;a <= 39 ;++a ) // a: 1->39
    {
        for( auto b : a5)
        {
            ll t= (1ull << a) *  b;
            if( t >up) break;
            a25.push_back(t);
        }
    }
    std::sort(a25.begin(),a25.end());

    // for( auto a : a25) std::cout << a << " ";
    // std::cout   << "\n";
}


//是否 y只有因子2 和 5
bool is_only_25(int y) {
    while( y % 2 == 0) y /=2;
    while( y % 5 == 0) y /=5;
    return y == 1;
}

int main () {
    init_a25();
    std::cin >> n;
    //枚举k
    for(int k = 1; k<=n;k++) {
        if( std::gcd(k,10) == 1) {
            ll cnt_x = n/k;
            ll cnt_y = f(n/k);
            ans += cnt_x * cnt_y; 
        }
    }
    std::cout << ans << "\n";
    
    return 0;
}
