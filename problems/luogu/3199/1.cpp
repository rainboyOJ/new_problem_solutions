/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-07 15:52:03
 */
#include <bits/stdc++.h>
#include <iomanip>
using namespace std;
typedef  double ll;

const int maxn = 2e6+5;
int n,m;
bool vis[maxn];
int a[maxn];

//oisnip_begindfs-spfa-判断负环是否存在.cpp
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3005;
const double INF = 1e9; 

// 邻接表存图 (目标点, 权值)
// 如果是 P3199 这种带参数的，权值计算可能在 dfs 内部动态算
struct Edge {
    int to;
    double w; 
};
vector<Edge> adj[MAXN];

// 建图辅助函数
void add_edge(int u, int v, double w) { adj[u].push_back({v, w}); }

double dis[MAXN];    // 记录距离
bool instack[MAXN];  // 【核心】记录当前递归栈中的节点 (是否是祖先)

// 【核心函数】DFS-SPFA
// u: 当前节点
// 返回值: true 表示发现负环, false 表示安全
bool spfa_dfs(int u, double x) {
    instack[u] = true; // 1. 入栈：标记 u 在当前路径上
    vis[u] = 1;

    for (auto &e : adj[u]) {
        int v = e.to;
        double w = e.w - x; 

        // 2. 松弛判断：只有能让距离变小，才继续走
        if (dis[v] > dis[u] + w) {
            dis[v] = dis[u] + w;

            // 3. 撞到祖先：如果 v 已经在栈里，说明在这个路径上绕回来了
            // 且满足松弛条件，说明环的权值和 < 0
            if (instack[v]) return true;

            // 4. 递归：继续往深处找，如果子路径发现环，直接上报
            if (spfa_dfs(v,x)) return true;
        }
    }

    instack[u] = false; // 5. 回溯：离开 u，出栈
    return false;
}


// 清空函数 (多测时使用)
void spfa_init(int _n) {
    n = _n;
    for (int i = 0; i <= n; i++) adj[i].clear();
}
//oisnip_end


void init(){
    std::cin >> n >> m;
    for(int i = 1;i <= m ;++i ) // i: 1->m
    {
        int u,v;
        double w;
        std::cin >> u >> v >> w;
        add_edge(u, v, w);
    }
}

bool check(double x) {

    // 初始化
    for (int i = 1; i <= n; i++) {
        dis[i] = 0;
        vis[i] = 0;
        instack[i] = false;
    }

    // 图是连通的
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        if( vis[i] ) continue;
        bool ret = spfa_dfs(i,x);
        if( ret ) return 1;
    }
    return 0;
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();
    double l = -1e7, r = 1e7;

    for(int i = 1;i <= 70 ;++i ) // i: 1->709
    {
        double mid = (l+r) / 2;
        if( check(mid) )
            r = mid;
        else
            l = mid;
    }
    
    cout << fixed << setprecision(8) << l << endl;
    
    return 0;
}
