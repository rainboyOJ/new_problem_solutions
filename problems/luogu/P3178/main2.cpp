/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 20:14
 * update_at: 2026-10-26 22:42
 */
// main2.cpp：P3178 树上操作，括号序（出栈入栈序）+ 两棵 2n 树状数组。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

int n, m;
ll weight[MAXN];      // 每个点的初始权值
vector<int> g[MAXN];  // 树的邻接表

int pos_in[MAXN];   // 节点入栈时在括号序里的位置
int pos_out[MAXN];  // 节点出栈时在括号序里的位置
int depth[MAXN];    // 深度，根为 1
int timer;          // 括号序计数器，取值 1..2n
int seq_len;        // 括号序长度，等于 2n

// 括号序上的普通树状数组：单点加、前缀求和。
struct Fenwick {
    ll tree[2 * MAXN]; // 每个点入栈、出栈各占一个位置

    void add(int pos, ll value) {
        for (int i = pos; i <= seq_len; i += i & -i) tree[i] += value;
    }

    ll prefix_sum(int pos) {
        ll answer = 0;
        for (int i = pos; i > 0; i -= i & -i) answer += tree[i];
        return answer;
    }
};

Fenwick bit_const; // 与查询点深度无关的那部分
Fenwick bit_depth; // depth[查询点] 的系数

// 一次 DFS 生成括号序：进入时分配一个位置，退出时再分配一个位置。
void dfs(int u, int fa) {
    pos_in[u] = ++timer;
    depth[u] = depth[fa] + 1;
    for (int v : g[u]) {
        if (v != fa) dfs(v, u);
    }
    pos_out[u] = ++timer;
}

// 在括号序的入栈、出栈两处做 ±value，使前缀和只统计到还留在栈里的节点。
void bracket_add(Fenwick &bit, int x, ll value) {
    bit.add(pos_in[x], value);
    bit.add(pos_out[x], -value);
}

int main() {
    scanf("%d%d", &n, &m);
    seq_len = 2 * n;
    for (int i = 1; i <= n; i++) scanf("%lld", &weight[i]);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    // 初始权值等价于对每个点各做一次「操作 1」。
    for (int i = 1; i <= n; i++) bracket_add(bit_const, i, weight[i]);

    while (m--) {
        int opt, x;
        ll a;
        scanf("%d%d", &opt, &x);
        if (opt == 1) {
            // 节点 x 加 a：x 及其每个后代 y 的路径和都正好多 a。
            scanf("%lld", &a);
            bracket_add(bit_const, x, a);
        } else if (opt == 2) {
            // 子树 x 加 a：子树内的查询点 y 多出 a * (depth[y] - depth[x] + 1)，
            // 拆成 a * depth[y] 与 a * (1 - depth[x]) 两部分分别累计。
            scanf("%lld", &a);
            bracket_add(bit_depth, x, a);
            bracket_add(bit_const, x, a * (1 - depth[x]));
        } else {
            // 入栈位置的前缀和只保留「入了栈还没出栈」的节点，它们恰好是 x 到根的路径。
            ll answer = bit_const.prefix_sum(pos_in[x])
                      + depth[x] * bit_depth.prefix_sum(pos_in[x]);
            printf("%lld\n", answer);
        }
    }
    return 0;
}
