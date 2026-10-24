/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-24 00:03
 * update_at: 2026-10-24 00:04
 */
#include <iostream>
#include <vector>

using namespace std;

// brute.cpp：小数据暴力模拟解，用来帮助理解题意并辅助对拍。
// 算法原理：严格按照题意，对每一张图 G_i (i=0..m)，以及每个点 u (1..n)，
// 模拟函数 f(u, G_i) 的计算过程：
// 依次枚举点 v=1..n，若当前子图中 u 能到达 v 且 v 能到达 u，则 cnt++，并将 v 及其关联边删除。
// 最后将所有 f(u, G_i) 累加得到 h(G_i)。
// 复杂度：单次连通性判定 O(n+m)，求一个 f(u) 需做 n 次 DFS 判定，求 h(G) 需 O(n^2(n+m))，
// 共有 m+1 张图，总时间复杂度 O(m * n^2 * (n+m))，仅适用于 n, m <= 15 的极小数据。

const int MAXN = 20;
const int MAXM = 50;

int n, m;
int u_edge[MAXM], v_edge[MAXM];

// 存储当前被激活的边集合与当前存活的点
bool edge_active[MAXM];
bool node_alive[MAXN];
bool vis[MAXN];

// DFS 判定在当前存活点与激活边构成的图中，从 src 是否能到达 dst
bool dfs_reach(int u, int dst) {
    if (u == dst) return true;
    vis[u] = true;
    for (int e = 1; e <= m; ++e) {
        if (!edge_active[e]) continue;
        if (u_edge[e] == u) {
            int v = v_edge[e];
            if (node_alive[v] && !vis[v]) {
                if (dfs_reach(v, dst)) return true;
            }
        }
    }
    return false;
}

bool can_reach(int src, int dst) {
    if (!node_alive[src] || !node_alive[dst]) return false;
    for (int i = 1; i <= n; ++i) vis[i] = false;
    return dfs_reach(src, dst);
}

// 计算当前图下的 f(u)
int calc_f(int u) {
    // 恢复所有点为存活状态
    for (int i = 1; i <= n; ++i) node_alive[i] = true;
    int cnt = 0;
    for (int v = 1; v <= n; ++v) {
        if (can_reach(u, v) && can_reach(v, u)) {
            cnt++;
            node_alive[v] = false; // 删除顶点 v
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> m)) return 0;
    for (int i = 1; i <= m; ++i) {
        cin >> u_edge[i] >> v_edge[i];
    }

    // G_0 是完整图，删除第 1..k 条边后的图为 G_k
    // 初始所有边都激活
    for (int i = 1; i <= m; ++i) edge_active[i] = true;

    vector<int> ans;
    for (int k = 0; k <= m; ++k) {
        if (k > 0) {
            edge_active[k] = false; // 删去第 k 条边
        }
        int total_h = 0;
        for (int u = 1; u <= n; ++u) {
            total_h += calc_f(u);
        }
        ans.push_back(total_h);
    }

    for (size_t i = 0; i < ans.size(); ++i) {
        cout << ans[i] << (i + 1 == ans.size() ? "" : " ");
    }
    cout << "\n";

    return 0;
}
