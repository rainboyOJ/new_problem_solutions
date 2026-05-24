#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
const int INF = 1e9;

struct Edge {
    int to, w;
};
vector<Edge> adj[MAXN];
int dis[MAXN];
bool instack[MAXN];
bool visited[MAXN]; // 全局访问标记，用于剪枝
int n, m;

// DFS-SPFA
bool spfa_dfs(int u) {
    instack[u] = true;
    visited[u] = true; // 标记该点已访问，后续外层循环不用再进

    for (auto &e : adj[u]) {
        int v = e.to;
        int w = e.w;

        if (dis[v] > dis[u] + w) {
            dis[v] = dis[u] + w;
            if (instack[v]) return true; // 发现负环
            if (spfa_dfs(v)) return true;
        }
    }
    instack[u] = false;
    return false;
}

void solve() {
    cin >> n >> m;
    
    // 1. 清空数据 (多测不清空，爆零两行泪)
    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        dis[i] = 0; // 判负环初始化为 0
        instack[i] = false;
        visited[i] = false;
    }

    // 2. 读入
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (w >= 0) {
            // 题目说：非负边是双向的
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        } else {
            // 负边是单向的
            adj[u].push_back({v, w});
        }
    }

    // 3. 判负环
    bool flag = false;
    for (int i = 1; i <= n; i++) {
        if (visited[i]) continue; // 剪枝：如果这个连通块搜过了，就跳过
        if (spfa_dfs(i)) {
            flag = true;
            break;
        }
    }

    if (flag) cout << "YES" << endl;
    else cout << "NO" << endl;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
