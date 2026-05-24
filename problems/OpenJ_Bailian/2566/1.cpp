/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-14 15:38:03
 */
#include <bits/stdc++.h>
#include <random>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,k,t;
int a[maxn];
struct node {
    ll sum;
    ll id;
    bool operator<(const node &t) const {
        return sum < t.sum;
    }
};

node pre[maxn]; //前缀和
void init(){

    pre[0].id = 0; pre[0].sum = 0;

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int t;
        std::cin >> t;
        pre[i].id  = i;
        pre[i].sum = pre[i-1].sum + t;
    }

    // 排序
    std::sort(pre,pre+1+n);

    #ifdef DEBUG
    for(int i = 0;i <= n ;++i ) // i: 1->n
    {
        cout << pre[i].sum << "\t";
    }
    std::cout  << "\n";
    for(int i = 0;i <= n ;++i ) // i: 1->n
    {
        cout << pre[i].id<< "\t";
    }
    std::cout  << "\n";
    #endif

}

ll _abs(ll v) {
    return v < 0 ? -v : v;
}

void solve() {
    std::cin >> t;
    if( t < 0 ) t *= -1;

    int l,r;
    ll min_abs_val= 1e10;
    ll ans;
    int j  = 0;
    //前面的指针
    for(int i = 0 ;i<= n; i++) 
    {

        j = max(j,i+1);
        for( ; j <= n ; j++ ) {
            ll val = pre[j].sum - pre[i].sum;

            // val 就是区间和绝对值
            int abs = _abs(val-t);


            // 记录, 
            if( abs < min_abs_val ) {
                ans = val;
                min_abs_val = abs;
                l = pre[i].id;
                r = pre[j].id;
            }
            // 后面肯定更大
            if( val >= t ) break; 

        }



        #ifdef DEBUG
        
        // std::cout << "i -> " << i << " \n";
        // std::cout << "j -> " << j  << " \n";
        // std::cout <<"val -> "  <<  val << "\n";
        // std::cout <<"ans-> "  <<  ans << "\n";
        // if( l > r) std::swap(l,r);
        // std::cout << "(l,r) = " <<  l << "," << r << "\n";
        // std::cout  << "-------------\n";
        // std::cout  << "\n";

        #endif
    }

    if( l > r) std::swap(l,r);
    l++;
    std::cout << ans   << " ";
    std::cout << l<< " ";
    std::cout << r<< "\n";
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    while (1) {
        std::cin >> n >> k;
        if( n ==0 && k == 0 ) break;
      
        init();
        for(int i = 1;i <= k ;++i ) // i: 1->k
        {
            solve();
        }

        // break;

    }
    
    return 0;
}
