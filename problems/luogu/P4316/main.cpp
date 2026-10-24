#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

typedef long long ll;

const int maxn = 100005;

struct Edge {
    int to;
    ll w;
};

int n, m;
vector<Edge> g[maxn];
int out_deg[maxn];
double f[maxn];
bool vis[maxn];

// dfs(u) 计算从节点 u 出发到达终点 n 的期望路径长度
double dfs(int u) {
    if (u == n) {
        return 0.0;
    }
    if (vis[u]) {
        return f[u];
    }
    vis[u] = true;
    
    double sum = 0.0;
    for (const auto &e : g[u]) {
        sum += (dfs(e.to) + (double)e.w);
    }
    
    // 全期望公式：以 1/out_deg[u] 的等概率走向每个后继节点
    f[u] = sum / (double)out_deg[u];
    return f[u];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    if (!(cin >> n >> m)) return 0;
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        out_deg[u]++;
    }
    
    cout << fixed << setprecision(2) << dfs(1) << "\n";
    
    return 0;
}
