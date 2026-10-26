/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:30
 * update_at: 2026-10-26 22:24
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;  // 本题 n <= 1e5
const int max_log = 20;   // 2^17 > 1e5，留一点余量

using Graph = vector<int>;
Graph tree[maxn];

int n, m, lg;           // lg = 实际需要的二进制位数，按 n 收紧
int depth[maxn];        // depth[0] = 0，根 depth = 1；0 号点当哨兵
int up[maxn][max_log];  // up[u][j] = u 的 2^j 级祖先，越界一律落到 0
int stk[maxn];          // 迭代 DFS 的手写栈

int dfn[maxn];    // dfn[u] 是 u 的 DFS 序
int sz[maxn];     // sz[u] 是 u 的子树大小
int order[maxn];  // order[k] 是 dfs 序第 k 个出栈的节点
int timer;        // DFS 序计时器

int bit[maxn];  // 差分数组 c[] 的树状数组（单点加、前缀和）

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

void init_lca(int n_) {
    n = n_;
    lg = 0;
    while ((1 << lg) <= n) ++lg;  // 最长上跳 n-1 层，只用到前 lg 位
    for (int u = 0; u <= n; ++u) {
        depth[u] = 0;
        for (int j = 0; j < lg; ++j) up[u][j] = 0;
    }
}

// 迭代 DFS：出栈时填 up[u][1..lg-1]，因为 u 的父亲和更高祖先早就填好了。
// 出栈顺序就是先序，所以在这里打 dfn；子树因此仍是连续区间。
void build_lca(int root = 1) {
    int top = 0;
    timer = 0;     // dfn / order / sz 每次重建，多测也不会留残留
    depth[0] = 0;  // 哨兵，保证根的父亲深度为 0
    depth[root] = 1;
    up[root][0] = 0;
    stk[top++] = root;
    while (top) {
        int u = stk[--top];
        dfn[u] = ++timer;
        order[timer] = u;
        for (int j = 1; j < lg; ++j) {
            up[u][j] = up[up[u][j - 1]][j - 1];  // 先跳 2^(j-1)，再跳 2^(j-1)
        }
        for (int v : tree[u]) {
            if (v == up[u][0]) continue;  // 只跳过父亲
            up[v][0] = u;
            depth[v] = depth[u] + 1;
            stk[top++] = v;
        }
    }
    // 先序的逆序里，儿子一定排在父亲前面，所以可以这样倒着累加子树大小。
    for (int u = 1; u <= n; ++u) sz[u] = 1;
    for (int k = n; k >= 2; --k) {
        int u = order[k];
        sz[up[u][0]] += sz[u];
    }
}

// u 的第 k 级祖先：k 的二进制里每个 1 位跳一次
int kth_ancestor(int u, int k) {
    for (int j = 0; j < lg; ++j) {
        if ((k >> j) & 1) u = up[u][j];
    }
    return u;
}

int lca(int a, int b) {
    if (depth[a] < depth[b]) swap(a, b);       // 让 a 是较深的点
    a = kth_ancestor(a, depth[a] - depth[b]);  // 先跳到同一层
    if (a == b) return a;                      // 已经重合，b 就是答案

    // 从大步到小步：跳到 LCA 的正下方，父节点就是答案
    for (int j = lg - 1; j >= 0; --j) {
        if (up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
        }
    }
    return up[a][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    init_lca(n);    // 单测可省；照模板留着，换多测也不会留残留
    build_lca(1);   // 以 1 为根：深度、倍增表、DFS 序、子树大小一次遍历全就位

    while (m--) {
        char op;
        int a, b;
        cin >> op >> a >> b;
        if (op == 'P') {
            // 路径 a->b 上的每条边 +1，转成三个点的边差分。
            int c = lca(a, b);
            bit_add(dfn[a], 1);
            bit_add(dfn[b], 1);
            bit_add(dfn[c], -2);
        } else {
            // Q：a、b 是一条边的两个端点，深的那一端代表这条边。
            int child = (depth[a] > depth[b]) ? a : b;
            // 边 (child, parent[child]) 的值 = 子树 child 的差分和，
            // 也就是 DFS 序上区间 [dfn[child], dfn[child] + sz[child] - 1] 的和。
            int ans = bit_prefix(dfn[child] + sz[child] - 1) - bit_prefix(dfn[child] - 1);
            cout << ans << '\n';
        }
    }

    return 0;
}
