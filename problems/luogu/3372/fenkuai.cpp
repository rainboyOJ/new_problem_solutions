#include <bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;

typedef  long long ll;
ll n,m;
ll a[maxn];


// ---- block
struct Block {
    ll block;
    ll t;
    ll pos[maxn];
    ll st[maxn];
    ll ed[maxn];

    ll sum[maxn];
    ll addflag[maxn];

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

        for(ll i = 1;i <= t ;++i ) // i: 1->t
        {
            for(ll j = st[i];j <= ed[i] ;++j ) // j: 1->n
            {
                sum[i] += a[j];
            }
        }
    }

    //区间修改 
    void update(ll L,ll R,ll d) {
        ll p = pos[L],q = pos[R];
        if( p == q) {
            for(ll i = L;i <= R;i++) {
                a[i] +=d;
                sum[p] +=d; 
            }
        }
        else {
            for(ll i = p+1;i <= q-1;i++) 
                addflag[i] += d;
            for(ll i = L; i <= ed[p] ;i++) {
                a[i] += d;
                sum[p] += d;
            }
            for(ll i = st[q];i <= R;i++) {
                a[i] += d;
                sum[q] += d;
            }
        }
    }

    long long query(ll L,ll R) {
        long long ret = 0;
        ll p = pos[L], q = pos[R];
        if( p == q) {
            for(ll i = L;i <= R;i++) {
                ret += a[i];
                ret += addflag[p];
            }
        }
        else {
            for(ll i = p+1;i<=q-1;i++) {
                ret += sum[i];
                ret += addflag[i] * (ed[i]-st[i]+1);
            }
            for(ll i = L; i <= ed[p] ;i++) {
                ret += a[i];
                ret += addflag[p];
            }
            for(ll i = st[q];i <= R;i++) {
                ret += a[i];
                ret += addflag[q];
            }
        }
        return ret;
    }
} myblock;


//读取数据
void init() {
    std::cin >> n;
    std::cin >> m;
    for(ll i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
    }
    myblock.init();
}



int main () {
    init();
    for(ll i = 1;i <= m ;++i ) // i: 1->m
    {
        ll opt;
        std::cin >> opt;
        if(opt == 1) {
            ll x,y,k;
            std::cin >> x >> y >> k;
            myblock.update(x, y, k);
        }
        else {
            ll x,y;
            std::cin >> x >> y;
            cout << myblock.query(x, y) << "\n";
        }
    }
    
    return 0;
}
