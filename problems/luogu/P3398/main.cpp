/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:59
 * update_at: 2026-08-12 22:59
 */
// main.cpp：P3398 仓鼠找 sugar 正式解。
// 以 rbook 模板 lca-binary-lifting 为基底：倍增预处理祖先表，O(log n) 查询 LCA。
// 判断两条树上路径 a-b 与 c-d 是否相交：
//   1) 两条路径相交当且仅当 lca(a,b) 在路径 c-d 上，或 lca(c,d) 在路径 a-b 上；
//   2) 点 x 在路径 u-v 上当且仅当 dist(u,x) + dist(x,v) == dist(u,v)（距离拆分）。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int LOG = 17; // 2^17 = 131072 > 1e5，按题目规模调整

vector<int> g[MAXN];      // 树的邻接表
int depth[MAXN];          // depth[u] 表示节点 u 的深度（根深度为 1）
int up[MAXN][LOG + 1];    // up[u][j] 表示节点 u 的 2^j 级祖先

// 预处理 depth 和倍增表 up[][]，fa 为父节点（根的父亲是 0）。
void dfs(int u, int fa) {
    up[u][0] = fa;
    depth[u] = depth[fa] + 1;
    for (int j = 1; j <= LOG; j++) {
        up[u][j] = up[up[u][j - 1]][j - 1];
    }
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs(v, u);
    }
}

// 查询节点 a 和 b 的最近公共祖先。
int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);

    // 先把深的点 a 提到与 b 同一深度，距离拆成二进制位依次跳。
    int diff = depth[a] - depth[b];
    for (int j = 0; j <= LOG; j++) {
        if (diff & (1 << j)) a = up[a][j];
    }
    if (a == b) return a;

    // 两个点一起从大到小跳，跳到 LCA 下面一层。
    for (int j = LOG; j >= 0; j--) {
        if (up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
        }
    }
    return up[a][0];
}

// 树上两点 u, v 的距离：depth[u] + depth[v] - 2 * depth[lca(u,v)]。
int dist(int u, int v) {
    int c = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[c];
}

// 判断点 x 是否在路径 u-v 上：用距离拆分等式。
// 树上唯一路径意味着 dist(u,x) + dist(x,v) == dist(u,v) 恰好表示 x 在 u 到 v 的路径上。
bool on_path(int x, int u, int v) {
    return dist(u, x) + dist(x, v) == dist(u, v);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        // 两条路径各自最高点：lca(a,b) 与 lca(c,d)。
        int p = lca(a, b);
        int r = lca(c, d);

        // 路径 a-b 与 c-d 相交：某一条路径的 LCA 落在另一条路径上。
        if (on_path(p, c, d) || on_path(r, a, b))
            cout << "Y\n";
        else
            cout << "N\n";
    }

    return 0;
}
