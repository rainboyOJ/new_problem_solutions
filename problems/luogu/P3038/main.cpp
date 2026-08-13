/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:30
 * update_at: 2026-08-12 22:30
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int LOG = 20; // 2^20 > 1e6，本题 n <= 1e5，按模板保持 20

int n, m;
vector<int> g[MAXN]; // 邻接表存树

int depth[MAXN];        // depth[u] 表示节点 u 的深度
int up[MAXN][LOG + 1];  // up[u][j] 表示 u 的 2^j 级祖先
int dfn[MAXN];          // dfn[u] 表示节点 u 的 DFS 序
int sz[MAXN];           // sz[u] 表示节点 u 的子树大小
int timer;              // DFS 序计时器

int bit[MAXN]; // 差分数组 c[] 的树状数组（单点加、前缀和）

// 树状数组：位置 pos 加上 value。
void bit_add(int pos, int value) {
    for (int i = pos; i <= n; i += i & -i) {
        bit[i] += value;
    }
}

// 树状数组：求差分数组 [1, pos] 的前缀和。
int bit_prefix(int pos) {
    int res = 0;
    for (int i = pos; i > 0; i -= i & -i) {
        res += bit[i];
    }
    return res;
}

// 预处理：按 BFS 顺序求父亲、深度，再倍增求 up[][j]。
// 用迭代写法，避免 10^5 深链上递归 DFS 撑爆系统栈。
void preprocess(int root) {
    vector<int> order; // BFS 访问顺序，父节点总在子节点之前
    order.push_back(root);
    depth[root] = 1;
    for (int i = 0; i < (int)order.size(); i++) {
        int u = order[i];
        for (int j = 0; j < (int)g[u].size(); j++) {
            int v = g[u][j];
            if (v == up[u][0]) continue; // 跳过父节点
            up[v][0] = u;
            depth[v] = depth[u] + 1;
            order.push_back(v);
        }
    }
    // 倍增转移：2^j 级祖先 = 先跳 2^(j-1)，再跳 2^(j-1)。
    for (int j = 1; j <= LOG; j++) {
        for (int i = 0; i < (int)order.size(); i++) {
            int u = order[i];
            up[u][j] = up[up[u][j - 1]][j - 1];
        }
    }
    // 子树大小：按 BFS 逆序向上累加。
    for (int i = 0; i < (int)order.size(); i++) {
        sz[order[i]] = 1;
    }
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        if (u != root) {
            sz[up[u][0]] += sz[u];
        }
    }
}

// 求节点 u 向上跳 k 层的祖先（k 拆成二进制位跳）。
int kth_ancestor(int u, int k) {
    for (int j = 0; j <= LOG; j++) {
        if (k & (1 << j)) {
            u = up[u][j];
        }
    }
    return u;
}

// 倍增求 a, b 的最近公共祖先。
int lca(int a, int b) {
    if (depth[a] < depth[b]) {
        swap(a, b);
    }
    a = kth_ancestor(a, depth[a] - depth[b]); // 先把深的点提到同一深度
    if (a == b) {
        return a;
    }
    for (int j = LOG; j >= 0; j--) {
        if (up[a][j] != up[b][j]) { // 还没跳过 LCA，可以一起跳
            a = up[a][j];
            b = up[b][j];
        }
    }
    return up[a][0]; // 最后停在 LCA 的两个儿子上
}

// 迭代栈求 DFS 序：保证每棵子树在 dfn 上是连续区间 [dfn[x], dfn[x] + sz[x] - 1]。
void dfs_order(int root) {
    vector<int> st;
    st.push_back(root);
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        timer++;
        dfn[u] = timer;
        for (int j = 0; j < (int)g[u].size(); j++) {
            int v = g[u][j];
            if (v != up[u][0]) {
                st.push_back(v);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    preprocess(1);
    dfs_order(1);

    while (m--) {
        char op;
        int a, b;
        cin >> op >> a >> b;
        if (op == 'P') {
            // 路径 u->v 上的每条边 +1，转成三个点的边差分。
            int c = lca(a, b);
            bit_add(dfn[a], 1);
            bit_add(dfn[b], 1);
            bit_add(dfn[c], -2);
        } else {
            // Q：a、b 是一条边的两个端点，深的那一端代表这条边。
            int child = (depth[a] > depth[b]) ? a : b;
            // 边 (child, parent[child]) 的值 = 子树 child 的差分和。
            int ans = bit_prefix(dfn[child] + sz[child] - 1) - bit_prefix(dfn[child] - 1);
            cout << ans << '\n';
        }
    }

    return 0;
}
