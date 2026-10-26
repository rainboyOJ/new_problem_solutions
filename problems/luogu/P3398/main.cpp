/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:59
 * update_at: 2026-10-26 16:36
 */
// P3398 仓鼠找 sugar
// 判两条树上路径 a-b 与 c-d 是否有公共点。
// 结论：相交 <=> lca(a,b) 在路径 c-d 上，或 lca(c,d) 在路径 a-b 上。
// 判点在路径上用距离拆分：x 在 u-v 上 <=> dist(u,x) + dist(x,v) == dist(u,v)。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5; // 节点数上限
const int LOG = 17;          // 2^17 = 131072 > 1e5，够跳任意深度差

typedef long long ll;

ll n;              // 节点数
ll q;              // 询问数
vector<int> g[maxn]; // g[u]：与 u 相邻的所有点
ll depth[maxn]; // depth[u]：u 到根（1 号点）的边数
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
    if (depth[a] < depth[b]) swap(a, b); // 让 a 是更深的那个

    // 第一步：把 a 提到与 b 同深度，按深度差的二进制位跳。
    ll diff = depth[a] - depth[b];
    for (int j = 0; j <= LOG; j++) {
        if (diff & (1 << j)) a = up[a][j];
    }
    if (a == b) return a; // b 本来就是 a 的祖先

    // 第二步：两个点一起往上跳，跳到 LCA 的下一层。
    for (int j = LOG; j >= 0; j--) {
        if (up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
        }
    }
    return up[a][0];
}

// 树上两点距离：按 LCA 拆成两段深度差。
ll dist(int u, int v) {
    int c = lca(u, v);
    return depth[u] + depth[v] - 2 * depth[c];
}

// 判断点 x 是否在路径 u-v 上。
// 树上 u 到 v 只有一条路径，x 不在上面时 dist(u,x)+dist(x,v) 会严格多出一截来回。
bool on_path(int x, int u, int v) {
    return dist(u, x) + dist(x, v) == dist(u, v);
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

    depth[0] = 0; // 0 号点是虚拟根，深度当 0，方便倍增越界
    dfs_build(1, 0);

    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        int p = lca(a, b); // 路径 a-b 上离根最近的点
        int r = lca(c, d); // 路径 c-d 上离根最近的点

        // 两条路径相交 <=> 某一方的「最高点」落在对方路径上。
        if (on_path(p, c, d) || on_path(r, a, b)) {
            cout << "Y\n";
        } else {
            cout << "N\n";
        }
    }

    return 0;
}
