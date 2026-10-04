/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:19
 * update_at: 2026-10-05 06:19
 */

// roj 1526 Blockade：删点后失联有序点对统计。
// 答案只由删点后各连通块大小的平方和决定，用一次迭代 Tarjan 求出每个割点切出的子树即可。

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 100005; // n <= 10^5
const int MAXM = 500005; // m <= 5 * 10^5

// 链式前向星，点编号与边编号都从 1 开始，0 表示空
int head[MAXN];      // head[u]：以 u 为起点的第一条边编号
int to[2 * MAXM];    // to[e]：第 e 条边的另一端点
int nxt[2 * MAXM];   // nxt[e]：第 e 条边的下一条边编号
int edge_cnt = 0;

ll dfn[MAXN];        // dfn[u]：DFS 序
ll low[MAXN];        // low[u]：子树 T_u 内通过回边能到达的最小 dfn
ll parent[MAXN];     // parent[u]：DFS 树上的父亲，根为 0
ll sub_size[MAXN];   // sub_size[u]：T_u 的子树大小
ll cut[MAXN];        // cut[u]：被 u 切出去的子树大小之和（low[c] >= dfn[u] 的儿子 c）
ll sq[MAXN];         // sq[u]：删去 u 后各连通块大小的平方和
ll order[MAXN];      // order[t]：dfn 为 t 的点，便于按 dfn 逆序处理
ll dfn_cnt = 0;      // 已分配的 dfn 个数

// 迭代 DFS 的手写栈：stk_u 存点，stk_e 存该点下一条待看的边编号
int stk_u[MAXN];
int stk_e[MAXN];
int top = 0;

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 迭代 Tarjan：一次 DFS 求出 dfn / low / parent，不用递归，深链不会爆栈。
void tarjan(ll n) {
    ll timer = 0;
    for (int root = 1; root <= n; root++) {
        if (dfn[root] != 0) {
            continue; // 图不连通时逐块起搜
        }
        timer++;
        dfn[root] = timer;
        low[root] = timer;
        order[timer] = root;
        parent[root] = 0;

        top = 0;
        top++;
        stk_u[top] = root;
        stk_e[top] = head[root];

        while (top > 0) {
            int u = stk_u[top];
            int e = stk_e[top];
            if (e != 0) {
                stk_e[top] = nxt[e]; // 这条边看完了，指针后移
                int v = to[e];
                if (dfn[v] == 0) {
                    timer++;
                    dfn[v] = timer;
                    low[v] = timer;
                    order[timer] = v;
                    parent[v] = u;
                    top++;
                    stk_u[top] = v;
                    stk_e[top] = head[v];
                } else if (v != parent[u]) {
                    // 回边：用 dfn[v] 而不是 low[v] 松弛
                    if (dfn[v] < low[u]) {
                        low[u] = dfn[v];
                    }
                }
            } else {
                top--; // u 的邻边看完，u 出栈
                int p = parent[u];
                if (p != 0 && low[u] < low[p]) {
                    low[p] = low[u]; // 出栈时才把子点的 low 回传给父亲
                }
            }
        }
    }
    dfn_cnt = timer;
}

// 按 dfn 从大到小（即 DFS 出栈顺序）累加子树大小，同时算出每个点的 sq。
// 儿子一定比父亲先处理，所以子树大小直接往父亲身上加，不需要额外的回溯。
void calc_blocks(ll n) {
    for (int u = 1; u <= n; u++) {
        sub_size[u] = 1;
        cut[u] = 0;
        sq[u] = 0;
    }
    for (ll t = dfn_cnt; t >= 1; t--) {
        int u = order[t];
        int p = parent[u];

        // 不是被切出的子树，剩下的点（祖先方向）合成最后一块
        ll rest = n - 1 - cut[u];
        sq[u] += rest * rest;

        if (p != 0) {
            if (low[u] >= dfn[p]) {
                // 子树 u 被 p 整块切出去
                sq[p] += sub_size[u] * sub_size[u];
                cut[p] += sub_size[u];
            }
            sub_size[p] += sub_size[u];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;
    for (ll i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }

    tarjan(n);
    calc_blocks(n);

    // 跨块有序点对 = (n-1)^2 - sq[u]，再加上 u 与其余 n-1 个点各自失联
    for (int u = 1; u <= n; u++) {
        ll ans = (n - 1) * (n - 1) - sq[u] + 2 * (n - 1);
        cout << ans << "\n";
    }

    return 0;
}
