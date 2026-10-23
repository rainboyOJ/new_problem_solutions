/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 23:00
 * update_at: 2026-10-23 20:30
 */
// main3.cpp：P3178 树上操作，树链剖分 + 双树状数组（区间加、区间和）。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

int n, m;
ll weight[MAXN];      // 每个点的初始权值
vector<int> g[MAXN];  // 树的邻接表

// 树链剖分相关数组
int parent[MAXN];    // 父亲
int depth[MAXN];     // 深度，根为 1
int subsize[MAXN];   // 子树大小
int heavy[MAXN];     // 重儿子（子树最大的那个儿子）
int chain_top[MAXN]; // 重链链头
int dfn[MAXN];       // 剖分后的新编号 1..n
int timer;           // dfn 分配计数器

// 双树状数组：同时支持区间加与区间和。
// bit_diff 存差分 b[i]，bit_weighted 存 i * b[i]，
// 前缀和按 P(x) = (x+1) * sum(b, x) - sum(i * b, x) 恢复。
struct RangeFenwick {
    ll bit_diff[MAXN];
    ll bit_weighted[MAXN];

    void add(ll *bit, int pos, ll value) {
        for (int i = pos; i <= n; i += i & -i) bit[i] += value;
    }

    ll sum(ll *bit, int pos) {
        ll answer = 0;
        for (int i = pos; i > 0; i -= i & -i) answer += bit[i];
        return answer;
    }

    // 原数组区间 [left, right] 每个位置都加上 value
    void range_add(int left, int right, ll value) {
        add(bit_diff, left, value);
        add(bit_diff, right + 1, -value);
        add(bit_weighted, left, value * left);
        add(bit_weighted, right + 1, -value * (right + 1));
    }

    ll prefix_sum(int pos) {
        return (ll)(pos + 1) * sum(bit_diff, pos) - sum(bit_weighted, pos);
    }

    ll range_sum(int left, int right) {
        return prefix_sum(right) - prefix_sum(left - 1);
    }
};

RangeFenwick bit;

// 第一次 DFS：求父亲、深度、子树大小与重儿子。
void dfs_size(int u, int fa) {
    parent[u] = fa;
    depth[u] = depth[fa] + 1;
    subsize[u] = 1;
    for (int v : g[u]) {
        if (v == fa) continue;
        dfs_size(v, u);
        subsize[u] += subsize[v];
        if (subsize[v] > subsize[heavy[u]]) heavy[u] = v;
    }
}

// 第二次 DFS：优先给重儿子编号，保证每条重链编号连续，子树编号也连续。
void dfs_number(int u, int top_node) {
    chain_top[u] = top_node;
    dfn[u] = ++timer;
    if (heavy[u] != 0) dfs_number(heavy[u], top_node);
    for (int v : g[u]) {
        if (v != parent[u] && v != heavy[u]) dfs_number(v, v);
    }
}

// 查询从 x 到根 1 的路径点权和：拆成若干条重链区间求和。
ll root_path_sum(int x) {
    ll answer = 0;
    while (chain_top[x] != chain_top[1]) {
        answer += bit.range_sum(dfn[chain_top[x]], dfn[x]);
        x = parent[chain_top[x]];
    }
    answer += bit.range_sum(dfn[1], dfn[x]);
    return answer;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%lld", &weight[i]);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs_size(1, 0);
    dfs_number(1, 1);

    // 初始权值：按剖分编号逐点放入（单点退化成区间加）。
    for (int i = 1; i <= n; i++) bit.range_add(dfn[i], dfn[i], weight[i]);

    while (m--) {
        int opt, x;
        ll a;
        scanf("%d%d", &opt, &x);
        if (opt == 1) { // 单点加：区间加退化成单点
            scanf("%lld", &a);
            bit.range_add(dfn[x], dfn[x], a);
        } else if (opt == 2) { // 子树加：子树在剖分序上是连续区间
            scanf("%lld", &a);
            bit.range_add(dfn[x], dfn[x] + subsize[x] - 1, a);
        } else { // 根路径和：逐段重链区间求和
            printf("%lld\n", root_path_sum(x));
        }
    }
    return 0;
}
