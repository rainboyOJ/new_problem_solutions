/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-07 09:17:48
 */
#include <bits/stdc++.h>
#include <iomanip>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const double  ninf = -1e10;

const int maxn = 2505;
const int maxe = 5005;
int n,m;
int K;
int a[maxn];
int S[maxn]; // 招募费用
int P[maxn]; // 战斗值
double dp[maxn][maxn]; // dp[u][i] 表示子树u选i个点的最大权值

//oisnip_beginlinklist_mini_struct.cpp
struct linkList {
    struct edge { int u, v,w, next; };
    edge e[maxe];
    int h[maxn], edge_cnt;
    linkList() { edge_cnt = 0; memset(h, -1, sizeof(h)); }
    void add(int u, int v,int w = 0) { e[edge_cnt] = {u, v,w, h[u]}; h[u] = edge_cnt++; }
    void add2(int u, int v,int w = 0) {
        add(u, v,w); add(v, u,w);
    }
} e;
//oisnip_end

void init(){
    std::cin >> K >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int s,p,r;
        std::cin >> s >> p >> r;
        e.add(r,i);
        S[i] = s;
        P[i] = p;
    }

}

void dfs_dp_tree(int u,double x) {

    if( u == 0) 
        dp[u][1] = 0;
    else 
        dp[u][1] = (double)P[u] - x * S[u];

    // 初始化
    for(int i = 2 ;i <= K+1 ;i++) dp[u][i] = ninf;

    for(int i = e.h[u] ; ~i ;i = e.e[i].next){
        int v = e.e[i].v;
        dfs_dp_tree(v,x);

        //无优化, 容量算到2就可以了
        for(int j = K+1; j>=2;j--) {

            // 分配给子树的容量,也是物品分组
            for(int k = 1 ;k <= j-1;k++) {
                if( dp[v][k] > ninf && dp[u][j-k] > ninf)
                    dp[u][j] = max(dp[u][j],dp[u][j-k] + dp[v][k]);
            }
        }
    }
}

bool check(double x) {
    dfs_dp_tree(0,x);

    return  dp[0][K+1] >=0;
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();

    //即使全是收益没有花费，最大值也就这么多
    double l  = 0, r= 10000;
    for(int i = 1;i <= 60 ;++i ) // i: 1->60
    {
        double mid = (l+r) /2;
        if( check(mid))
            l = mid; //成立
        else
            r = mid;
    }
    std::cout << fixed << setprecision(3) << l << "\n";
    
    return 0;
}
