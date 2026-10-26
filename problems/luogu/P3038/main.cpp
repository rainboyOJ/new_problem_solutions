/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:30
 * update_at: 2026-10-26 22:32
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 100005;  // 本题 n <= 1e5
const int max_log = 20;   // 2^17 > 1e5，留一点余量

using Graph = vector<int>;
Graph tree[maxn];

int n, m, lg;           // lg = 实际需要的二进制位数，按 n 收紧，不做无用功
int depth[maxn];        // depth[0] = 0，根 depth = 1；0 号点当哨兵
int up[maxn][max_log];  // up[u][j] = u 的 2^j 级祖先，越界一律落到 0

int dfn[maxn];  // dfn[u] 是 u 的 DFS 序
int sz[maxn];   // sz[u] 是 u 的子树大小
int timer;      // DFS 序计时器

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

// 递归 DFS：进点时就填好 depth 和 up[u][1..lg-1]。
// 走到 u 时父亲的整行已经算完，所以 u 的 2^j 级祖先可以直接拿来拼。
// 本题另外在进点时打 dfn 时间戳、回溯时累加 sz，供子树和查询使用。
void dfs(int u, int fa) {
    depth[u] = depth[fa] + 1;  // fa 为 0 时正好得到根 depth = 1
    up[u][0] = fa;
    for (int j = 1; j < lg; ++j) {
        up[u][j] = up[up[u][j - 1]][j - 1];  // 先跳 2^(j-1)，再跳 2^(j-1)
    }

    dfn[u] = ++timer;  // 进点先后就是先序，子树因此落在连续区间里
    sz[u] = 1;
    for (int v : tree[u]) {
        if (v == fa) continue;  // 只跳过父亲，其余都是儿子
        dfs(v, u);
        sz[u] += sz[v];  // 回溯时把子树的点并进来
    }
}

// 预处理：清空上一组的残留，再从 root 递归灌满 depth 与 up。
// 多测时每组都要重新调用，否则会读到上一张图的祖先表。
void init_lca(int n_, int root = 1) {
    n = n_;
    lg = 0;
    while ((1 << lg) <= n) ++lg;  // 最长上跳 n-1 层，只用到前 lg 位
    for (int u = 0; u <= n; ++u) {
        depth[u] = 0;
        for (int j = 0; j < lg; ++j) up[u][j] = 0;
    }
    timer = 0;      // dfn 与 sz 也跟着本组重来
    dfs(root, 0);   // 哨兵点 0：depth[0] = 0、up[0][*] = 0，越界都落到这里
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

    init_lca(n, 1);  // n 个点、以 1 为根：深度、倍增表、DFS 序、子树大小一次 DFS 全就位

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
