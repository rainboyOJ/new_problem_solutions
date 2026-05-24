/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-19 15:05:06
 */
#include <bits/stdc++.h>
#include <vector>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 1e6+5;
const int maxe = 2e6+5;
int n,m;
int a[maxn]; // a[i] 第i个人的战斗力 
int hates[maxn]; // 记录 u 痛恨 v，用于找环

bool vis[maxn];
int mark;

ll dp[maxn][2]; //dp[i][0] 不选i的时候的值

//邻接表存图,这里我偷懒了,使用的vec
std::vector<int> g[maxn]; 
 
void init(){
    std::cin >> n;

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        int v;
        std::cin >> a[i] >>v; 
        hates[i] = v;

        // nxt[v] = i;  
        g[v].push_back(i);
        //反向建图
        // 保证环上的dfs,可以访问到所有的点
    }
}

//内向基环树找环上点
int find_node_at_cycle(int u) {
    while(!vis[u]) {
        vis[u] = 1;
        u = hates[u];
    }
    return u;
}

void dfs_dp(int u) {
    // 这里加上这个,
    // 因为find_node_at_cycle 不一定可以访问到所有的点
    vis[u] = 1; 

    // 初始化
    dp[u][0] = 0;
    dp[u][1] = a[u];

    // 因为mark一定不选,那么 就不用考虑mark影响
    // 所以到mark的这个边,不用考虑
    // 能到mark的这个点,其实是叶子结点
    for( auto v : g[u]) {
        if( v == mark)  continue;
        dfs_dp(v);

        dp[u][1] += dp[v][0];
        dp[u][0] += std::max(dp[v][0],dp[v][1]);

    }
}


ll solve(int u) {
    ll res = 0;
    // 此时 v 一定是环上的一个点
    int v = find_node_at_cycle(u);
    mark  = v; //v 不选, 则father[v] -> v  
    dfs_dp(v);
    res =  dp[v][0];

    mark = hates[v];
    dfs_dp(hates[v]);
    res =  std::max(res, dp[mark][0]);

    return res;
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();
    
    ll ans = 0;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        if(vis[i] == 0) {
            //求从i开始的连通块的值
            ans += solve(i);
        }
    }
    std::cout << ans << "\n";
    return 0;
}
