#include <algorithm>
#include <bits/stdc++.h>
using namespace std;
const int maxn =  2e6+5;
typedef long long ll;
ll n,m;
ll a[maxn];


// ---- block
struct Block {
    ll block;
    ll t;
    ll pos[maxn];
    ll st[maxn];
    ll ed[maxn];

    // ll sum[maxn];
    ll addflag[maxn];
    const int maxn_block = 2005;
    vector<ll> sorted_blocks[2005]; // 新增：存储每个块排序后的副本

    void init(){
        block = sqrt(n);
        t = n / block;
        if( n % block) t++;
        for(ll i = 1;i <= t ;++i ) // i: 1->t
        {
            st[i] = (i-1) * block + 1;
            ed[i] = i * block;
        }
        ed[t] = n; // 修正最后一个快的结尾
        for(ll i = 1;i <= n ;++i ) // i: 1->n
        {
            pos[i] = (i-1) / block + 1;
        }

        // 初始化 sorted_blocks
        for (ll i = 1; i <= t; ++i) {
            addflag[i] = 0; // 初始化懒标记
            sorted_blocks[i].clear();
            for (ll j = st[i]; j <= ed[i]; ++j) {
                sorted_blocks[i].push_back(a[j]);
            }
            std::sort(sorted_blocks[i].begin(), sorted_blocks[i].end());
        }

        // for(ll i = 1;i <= t ;++i ) // i: 1->t
        // {
        //     for(ll j = st[i];j <= ed[i] ;++j ) // j: 1->n
        //     {
        //         sum[i] += a[j];
        //     }
        // }
    }
    
    // 辅助函数：重建并排序指定块
    void reset_block(int b) {
        sorted_blocks[b].clear();
        for (ll i = st[b]; i <= ed[b]; ++i) {
            sorted_blocks[b].push_back(a[i]);
        }
        std::sort(sorted_blocks[b].begin(), sorted_blocks[b].end());
    }

    //区间修改 
    void update(ll L,ll R,ll d) {
        ll p = pos[L],q = pos[R];
        if( p == q) {
            for(ll i = L;i <= R;i++) {
                a[i] +=d;
            }
            // std::sort(a+st[p],a+ed[p]+1); //重新排序
            reset_block(p);
        }
        else {
            for(ll i = p+1;i <= q-1;i++) 
                addflag[i] += d;
            for(ll i = L; i <= ed[p] ;i++) {
                a[i] += d;
            }
            for(ll i = st[q];i <= R;i++) {
                a[i] += d;
            }
            reset_block(p);
            reset_block(q);
        }
    }

    long long query(ll L,ll R,ll val) {
        long long ret = 0;
        ll p = pos[L], q = pos[R];
        if( p == q) {
            for(ll i = L;i <= R;i++) {
                if( a[i] + addflag[p] >= val) ++ret;
            }
        }
        else {
            for(ll i = p+1;i<=q-1;i++) {
                // a[i] + flag >= c
                // a[i] >= c- flag
                ll new_val = val-addflag[i];
                // 在排序后的 vector 上进行二分查找
                std::vector<ll>::iterator it = lower_bound(sorted_blocks[i].begin(), sorted_blocks[i].end(), new_val);
                ret += (sorted_blocks[i].end() - it);
            }
            for(ll i = L; i <= ed[p] ;i++) {
                if( a[i] + addflag[p] >= val) ++ret;
            }
            for(ll i = st[q];i <= R;i++) {
                if( a[i] + addflag[q] >= val) ++ret;
            }
        }
        return ret;
    }
} myblock;

void init() {
    std::cin >> n >> m;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
    }
}


int main() {
    init();
    myblock.init();
    for(int i = 1;i <= m ;++i ) // i: 1->n
    {
        char opt;
        int x,y;
        int key;
        std::cin >> opt >> x >> y;
        std::cin >> key;
        if( opt == 'M') {
            myblock.update(x,y,key);
        }
        else {
            cout << myblock.query(x, y,key) << endl;
        }
        
    }
    

    return 0;
}
