/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:50
 * update_at: 2026-10-05 07:50
 */

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 100005; // 节点数上限 1e5
const int LOG = 17;      // 2^17 = 131072 > 1e5，倍增跳 depth 最多用到第 16 位

// 主要边构成一棵树，用链式前向星存无向边（每条边加两次）
int head[MAXN];      // head[u]：u 的第一条出边编号，-1 表示无边
int to[2 * MAXN];    // to[e]：第 e 条边的终点
int nxt[2 * MAXN];   // nxt[e]：第 e 条边的下一条兄弟边
int edge_cnt = 0;

int parent[MAXN]; // parent[v]：v 在根为 1 的树上的父亲，根的父亲为 0
int depth[MAXN];  // depth[v]：v 到根的边数
int order[MAXN];  // order[i]：迭代 DFS 第 i 个出栈的节点（先根顺序）
int order_cnt = 0;

int up[LOG][MAXN]; // up[k][v]：v 向上跳 2^k 步到达的祖先

int diff[MAXN]; // diff[u] 树上差分：后序累加后等于边 (parent[u], u) 被附加边跨越的次数，不超过 M=2e5，用 int 即可

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 以 1 为根迭代 DFS，求出 parent、depth 和先根序 order（避免递归爆栈）
void build_tree(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = 0;
    }
    parent[1] = 0;
    depth[1] = 0;
    order_cnt = 0;

    int stack[MAXN];
    int top = 0;
    stack[++top] = 1;
    while (top > 0) {
        int u = stack[top--];
        order_cnt++;
        order[order_cnt] = u;
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (v == parent[u]) {
                continue;
            }
            parent[v] = u;
            depth[v] = depth[u] + 1;
            stack[++top] = v;
        }
    }
}

// 在树上预处理倍增表：up[k][v] = up[k-1][ up[k-1][v] ]
void build_up(int n) {
    for (int v = 1; v <= n; v++) {
        up[0][v] = parent[v];
    }
    for (int k = 1; k < LOG; k++) {
        for (int v = 1; v <= n; v++) {
            up[k][v] = up[k - 1][up[k - 1][v]];
        }
    }
}

// 倍增求 u、v 的最近公共祖先
int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        int t = u;
        u = v;
        v = t;
    }
    // 先把更深的 u 抬到与 v 同深度
    int d = depth[u] - depth[v];
    for (int k = 0; k < LOG; k++) {
        if ((d >> k) & 1) {
            u = up[k][u];
        }
    }
    if (u == v) {
        return u;
    }
    // 再让两者同步上跳，停在 LCA 的正下方
    for (int k = LOG - 1; k >= 0; k--) {
        if (up[k][u] != up[k][v]) {
            u = up[k][u];
            v = up[k][v];
        }
    }
    return up[0][u];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }
    for (int i = 1; i <= n - 1; i++) {
        int a, b;
        cin >> a >> b;
        add_edge(a, b);
        add_edge(b, a);
    }

    build_tree(n);
    build_up(n);

    // 每条附加边 (u, v) 会给树上路径 u->v 上的每条主要边 +1，
    // 用树上差分：diff[u]++, diff[v]++, diff[lca(u,v)] -= 2
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        int w = lca(u, v);
        diff[u]++;
        diff[v]++;
        diff[w] -= 2;
    }

    // 按先根序倒序（即后序）累加差分，得到每条主要边的跨越次数 c：
    //   c == 0：第一步已断开，第二步 M 条附加边任选，贡献 M
    //   c == 1：只能切那条唯一的跨边，贡献 1
    //   c >= 2：怎么切都还连通，贡献 0
    ll ans = 0;
    for (int i = order_cnt; i >= 1; i--) {
        int u = order[i];
        if (u == 1) {
            continue;
        }
        int c = diff[u];
        if (c == 0) {
            ans += m;
        } else if (c == 1) {
            ans += 1;
        }
        diff[parent[u]] += c; // 把这条边的跨越次数并入父边
    }

    cout << ans << "\n";

    return 0;
}
