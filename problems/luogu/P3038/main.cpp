/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:30
 * update_at: 2026-10-26 22:15
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, m;
vector<int> g[MAXN]; // 全局邻接表数组：直接向 g[u] 加无权边

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

// 倍增算法求最近公共祖先（LCA），照 rbook 的「倍增 LCA」模板（code/tree/jump_lca.cpp）。
// 本题另外需要在 dfs 里顺手求出 DFS 序与子树大小，用于把子树和化成区间和。
struct BinaryLCA {
    constexpr static int maxn = MAXN;
    constexpr static int max_log = 20; // 2^20 > 1e5

    int depth[maxn];
    int up[maxn][max_log]; // up[u][j] 表示节点 u 的 2^j 级祖先
    int dfn[maxn];         // 本题额外维护：dfn[u] 是 u 的 DFS 序
    int sz[maxn];          // 本题额外维护：sz[u] 是 u 的子树大小
    int timer = 0;         // DFS 序计时器

    // DFS 预处理每个节点的深度 depth 以及 2^j 级祖先表 up
    void dfs(int u, int fa) {
        up[u][0] = fa;
        depth[u] = depth[fa] + 1;
        for (int j = 1; j < max_log; ++j) {
            up[u][j] = up[up[u][j - 1]][j - 1];
        }

        dfn[u] = ++timer; // 进入时打时间戳，子树因此落在连续区间里
        sz[u] = 1;
        for (int v : g[u]) {
            if (v == fa) continue;
            dfs(v, u);
            sz[u] += sz[v]; // 回溯时把子树的点并进来
        }
    }

    // 构建/预处理 LCA 倍增表，默认以 root 为根节点
    void build(int root = 1) {
        depth[0] = 0;
        dfs(root, 0);
    }

    // 查询节点 u 的第 k 级祖先（向上跳 k 步）
    int kth_ancestor(int u, int k) {
        for (int j = 0; j < max_log; ++j) {
            if (k & (1 << j)) u = up[u][j];
        }
        return u;
    }

    // 查询节点 a 和节点 b 的最近公共祖先（LCA）
    int lca(int a, int b) {
        // 保证 a 是较深节点
        if (depth[a] < depth[b]) swap(a, b);

        a = kth_ancestor(a, depth[a] - depth[b]);
        if (a == b) return a;

        for (int j = max_log - 1; j >= 0; --j) {
            if (up[a][j] != up[b][j]) {
                a = up[a][j];
                b = up[b][j];
            }
        }
        return up[a][0];
    }
};

BinaryLCA tree; // 整棵树只有一份倍增表，直接开全局对象

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

    tree.build(1); // 以 1 为根：深度、倍增表、DFS 序、子树大小一次 DFS 全就位

    while (m--) {
        char op;
        int a, b;
        cin >> op >> a >> b;
        if (op == 'P') {
            // 路径 a->b 上的每条边 +1，转成三个点的边差分。
            int c = tree.lca(a, b);
            bit_add(tree.dfn[a], 1);
            bit_add(tree.dfn[b], 1);
            bit_add(tree.dfn[c], -2);
        } else {
            // Q：a、b 是一条边的两个端点，深的那一端代表这条边。
            int child = (tree.depth[a] > tree.depth[b]) ? a : b;
            // 边 (child, parent[child]) 的值 = 子树 child 的差分和，
            // 也就是 DFS 序上区间 [dfn[child], dfn[child] + sz[child] - 1] 的和。
            int ans = bit_prefix(tree.dfn[child] + tree.sz[child] - 1) - bit_prefix(tree.dfn[child] - 1);
            cout << ans << '\n';
        }
    }

    return 0;
}
