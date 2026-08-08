/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-09 17:39:05
 */
#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

const int MAXN = 100005;

// 邻接表
vector<int> adj[MAXN];
int p[MAXN]; // 人流量
int n;
double k;

// DP 数组: dp[i][0] 不选, dp[i][1] 选
long long dp[MAXN][2]; 

// 记录环上的两个端点
int S, T;

// 并查集用于找环
struct DSU {
    int fa[MAXN];
    void init(int size) {
        for(int i=0; i<=size; i++) fa[i] = i;
    }
    int find(int x) {
        return x == fa[x] ? x : fa[x] = find(fa[x]);
    }
    bool merge(int x, int y) {
        int fx = find(x);
        int fy = find(y);
        if (fx != fy) {
            fa[fx] = fy;
            return true;
        }
        return false;
    }
} dsu;

// 树形DP函数
void dfs(int u, int fa) {
    dp[u][0] = 0;
    dp[u][1] = p[u];
    
    for (int v : adj[u]) {
        if (v == fa) continue; // 防止走回头路
        dfs(v, u);
        
        // 状态转移
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }
}

int main() {
    // 优化输入输出
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    
    dsu.init(n);
    
    // 读入边并处理基环
    for (int i = 0; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        // 如果 u和v 已经连通，说明这条边构成了环
        if (!dsu.merge(u, v)) {
            S = u;
            T = v;
            // !!! 关键点在这里 !!!
            // 发现这条边 (u, v) 会构成环，我们只记录端点 S=u, T=v
            // 注意：并没有执行 adj[u].push_back(v);
            // 这条边被物理上“丢弃”了，没有存入邻接表 adj 中
            // 相当于: 删除了 u 在环上的边
        } else {
            // 否则这是一条树边，加入邻接表
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    
    cin >> k;

    // 情况1：强制不选 S
    // 我们以 S 为根进行 DFS，最后取 dp[S][0]
    // 这里的 dp[S][0] 意味着 S 没被选，那么 T 选不选都无所谓，符合边(S,T)的约束
    memset(dp, 0, sizeof(dp));
    dfs(S, -1);
    long long ans1 = dp[S][0];
    
    // 情况2：强制不选 T
    // 我们以 T 为根进行 DFS，最后取 dp[T][0]
    memset(dp, 0, sizeof(dp));
    dfs(T, -1);
    long long ans2 = dp[T][0];
    
    // 结果计算
    double final_ans = max(ans1, ans2) * k;
    
    // 输出保留一位小数
    cout << fixed << std::setprecision(1) << final_ans << endl;

    return 0;
}
