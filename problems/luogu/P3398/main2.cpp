/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-24 14:05
 * update_at: 2026-10-26 16:36
 */
// P3398 仓鼠找 sugar
// 解法二：只比较两次「路径长度 + 交叉距离」，全程 4 次 LCA，代码最短。
// 结论：a-b 与 c-d 相交 <=> dist(a,b) + dist(c,d) >= dist(a,c) + dist(b,d)。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5; // 节点数上限
const int LOG = 17;          // 2^17 = 131072 > 1e5

typedef long long ll;

ll n;                  // 节点数
ll q;                  // 询问数
vector<int> g[maxn];   // g[u]：与 u 相邻的所有点
ll depth[maxn];   // depth[u]：u 到根（1 号点）的边数
int up[maxn][LOG + 1]; // up[u][j]：u 的 2^j 级祖先，越界时为 0

// 预处理深度与倍增表。
void dfs_build(int u, int fa) {
    depth[u] = depth[fa] + 1;
    up[u][0] = fa;
    for (int j = 1; j <= LOG; j++) {
        up[u][j] = up[up[u][j - 1]][j - 1];
    }
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs_build(v, u);
    }
}

// 倍增求 LCA，O(log n)。
int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);
    ll diff = depth[a] - depth[b];
    for (int j = 0; j <= LOG; j++) {
        if (diff & (1 << j)) a = up[a][j];
    }
    if (a == b) return a;
    for (int j = LOG; j >= 0; j--) {
        if (up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
        }
    }
    return up[a][0];
}

// 树上两点距离。
ll dist(int u, int v) {
    int c = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[c];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (ll i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    depth[0] = 0;
    dfs_build(1, 0);

    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        // 同一个端点配对（a-b、c-d）的距离和，不小于交叉配对（a-c、b-d）的距离和
        // 就说明两条路径有公共点。证明见题解。
        ll same_side = dist(a, b) + dist(c, d);
        ll cross_side = dist(a, c) + dist(b, d);

        if (same_side >= cross_side) {
            cout << "Y\n";
        } else {
            cout << "N\n";
        }
    }

    return 0;
}
