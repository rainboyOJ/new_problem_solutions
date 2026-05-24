// 发现 ai >=0, 那么可以不用前缀和数组
#include <bits/stdc++.h>
#include <cmath>
using namespace std;
typedef long long ll;
const int maxn = 1e5+6;
ll a[maxn]; // 前缀和
ll P[maxn]; // 前缀和
int n;

void init() {
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
        P[i] = a[i] +P[i-1]; 
    }
}

ll sum(int l,int r) {
    return P[r] - P[l-1];
}

void  work() {
    ll ans = 0;

    for(int k = 0;k<=34;k++) {

        // 坑点
        ll lower_bound = (1ull << ll(k));
        if( k == 0) lower_bound = 0;
        ll up_bound = (1ull << ll(k+1) );

        ll j1 = 0,j2 = 0;
        // 枚举起点
        for(ll i = 1 ; i <=  n;i++) {
            j1 = std::max(j1,i);

            // ll sum = P[j1].val - P[i].val;
            // 第一个 sum >= lower_bound的位置
            while(sum(i,j1) < lower_bound && j1 <=n) j1++; 
                
            j2 = std::max(j2,j1);
            // 第以个 sum >= up_bound的位置
            while(sum(i,j2) < up_bound && j2 <=n ) j2++;

            // 没有超过边界
            if( j1 <= n) {
                // cout << "k = " << k << " " ;
                // cout << "i = "  << i << ' ';
                // cout << "j1 = " << j1 << ' ';
                // cout << "j2 = " << j2 << ' ';
                ll ij_plus_sum = i * (j2 - j1) + (j2-1+j1) * (j2-j1) / 2;
                ll sum_k =  (k+1) * ij_plus_sum;
                // cout 
                ans += sum_k;
                // cout << "sum_k = " << sum_k << " \n";
            }
        }

    }


    std::cout << ans << "\n";
}

int main (int argc, char *argv[]) {
    int T;
    std::cin >> T;
    while (T--) {
        init();
        work();
    }
    
    return 0;
}