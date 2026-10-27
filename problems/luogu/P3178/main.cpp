/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 20:05
 * update_at: 2026-10-27 09:35
 */
// main.cpp：P3178 树上操作，DFS 序 + 贡献法 + 两棵差分树状数组。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

int n, m;
ll weight[MAXN];      // 每个点的初始权值
vector<int> g[MAXN];  // 树的邻接表

int dfn_in[MAXN];  // 节点的进入时间戳
int dfn_out[MAXN]; // 节点子树在时间戳上的右端点，子树区间为 [dfn_in[x], dfn_out[x]]
int depth[MAXN];   // 深度，根为 1
int timer;         // 时间戳计数器

// 「区间加、单点查」树状数组：区间 [left, right] 加 value 只需在差分数组上改两处，
// 单点查 pos 的值就是差分数组的前缀和。
struct Fenwick {
    ll tree[MAXN];

    void add(int pos, ll value) {
        for (int i = pos; i <= n; i += i & -i) tree[i] += value;
    }

    ll prefix_sum(int pos) {
        ll answer = 0;
        for (int i = pos; i > 0; i -= i & -i) answer += tree[i];
        return answer;
    }

    void range_add(int left, int right, ll value) {
        add(left, value);
        add(right + 1, -value); // right + 1 超过 n 时，上面的循环自然不执行
    }
};

Fenwick bit_const; // 贡献中与查询点深度无关的部分
Fenwick bit_depth; // 贡献中 depth[查询点] 的系数

// 一次 DFS 求出进入时间戳、子树右端点与深度。
void dfs(int u, int fa) {
    dfn_in[u] = ++timer;
    depth[u] = depth[fa] + 1;
    for (int v : g[u]) {
        if (v != fa) dfs(v, u);
    }
    dfn_out[u] = timer; // 回溯时 timer 恰好停在子树的最后一个节点上
}

// 节点 x 加 value：x 及其每个后代作为查询点时，路径和都正好多 value。
void point_add(int x, ll value) {
    bit_const.range_add(dfn_in[x], dfn_out[x], value);
}

// 子树 x 加 value：子树内的查询点 y 多出 value * (depth[y] - depth[x] + 1)，
// 拆成 value * depth[y] 与 value * (1 - depth[x]) 两部分分别累计。
void subtree_add(int x, ll value) {
    bit_depth.range_add(dfn_in[x], dfn_out[x], value);
    bit_const.range_add(dfn_in[x], dfn_out[x], value * (1 - depth[x]));
}

// 查询 x 到根的路径点权和。
ll root_path_sum(int x) {
    return bit_const.prefix_sum(dfn_in[x]) + depth[x] * bit_depth.prefix_sum(dfn_in[x]);
}

int main() {
    // 输入量到 1e5 级别，关掉同步后 cin 与 scanf 同量级。
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) cin >> weight[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    // 初始权值等价于对每个点各做一次「操作 1」。
    for (int i = 1; i <= n; i++) point_add(i, weight[i]);

    while (m--) {
        int opt, x;
        ll a;
        cin >> opt >> x;
        if (opt == 1) {
            cin >> a;
            point_add(x, a);
        } else if (opt == 2) {
            cin >> a;
            subtree_add(x, a);
        } else {
            cout << root_path_sum(x) << '\n';
        }
    }
    return 0;
}
