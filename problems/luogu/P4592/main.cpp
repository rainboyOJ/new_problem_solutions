/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 12:30
 * update_at: 2026-08-05 12:30
 */
// 可持久化 01-Trie：
//   子树查询：DFS 序把子树变成连续区间，在 dfn 序版本 Trie 上做区间异或最大值
//   路径查询：根到节点的版本 Trie 做四版本差（x + y - lca - fa[lca]）
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXLOG = 30;                       // 值 < 2^30，处理第 0..29 位
const int MAXNODE = MAXN * 2 * (MAXLOG + 1); // 两个逻辑 Trie 共用一个节点池

int n, q;
int val[MAXN];          // 节点权值

// 链式前向星
int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], edge_cnt;

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 可持久化 01-Trie 节点池
int ch[2][MAXNODE];   // 两个孩子
int sz[MAXNODE];      // 该节点子树中的元素个数
int tot;              // 节点池大小

// 在旧版本 old 上插入 x，返回新版本根
int trie_insert(int old, int x) {
    int now = ++tot;
    int cur = now, pre = old;
    sz[cur] = sz[pre] + 1;
    for (int b = MAXLOG - 1; b >= 0; b--) {
        int c = (x >> b) & 1;
        ch[c][cur] = ++tot;
        ch[!c][cur] = ch[!c][pre];   // 未改变的分支直接指向旧版本
        cur = ch[c][cur];
        pre = ch[c][pre];
        sz[cur] = sz[pre] + 1;
    }
    return now;
}

// 查询版本差区间 (lv, rv] 内与 x 异或的最大值
int trie_query_interval(int lv, int rv, int x) {
    int res = 0;
    for (int b = MAXLOG - 1; b >= 0; b--) {
        int c = (x >> b) & 1, want = c ^ 1;   // 优先走相反位
        if (sz[ch[want][rv]] - sz[ch[want][lv]] > 0) {
            res |= (1 << b);
            lv = ch[want][lv];
            rv = ch[want][rv];
        } else {
            lv = ch[c][lv];
            rv = ch[c][rv];
        }
    }
    return res;
}

// 查询四版本差 (a + b - c - d) 内与 x 异或的最大值（路径查询用）
int trie_query_path(int a, int b, int c, int d, int x) {
    int res = 0;
    for (int bit = MAXLOG - 1; bit >= 0; bit--) {
        int w = (x >> bit) & 1, want = w ^ 1;
        int cnt = sz[ch[want][a]] + sz[ch[want][b]] - sz[ch[want][c]] - sz[ch[want][d]];
        if (cnt > 0) {
            res |= (1 << bit);
            a = ch[want][a]; b = ch[want][b]; c = ch[want][c]; d = ch[want][d];
        } else {
            a = ch[w][a]; b = ch[w][b]; c = ch[w][c]; d = ch[w][d];
        }
    }
    return res;
}

// DFS 序、子树大小、深度、倍增、根到节点的版本 Trie
int dfn[MAXN], dfn_node[MAXN], sub_size[MAXN], dfn_cnt;
int depth[MAXN], fa[MAXN][18];
int root_path[MAXN];   // root_path[x]：根到 x 的路径上所有权值的版本
int root_dfn[MAXN];    // root_dfn[i]：dfn 序前 i 个节点的版本

// 显式栈迭代 DFS，避免链式数据递归爆栈
struct StackItem {
    int u, f, e;   // 当前节点、父节点、下一条要处理的边
};
StackItem stk[MAXN];
int stk_top;

void dfs1() {
    stk_top = 1;
    stk[1] = {1, 0, head[1]};

    // 进入根节点 1
    dfn[1] = ++dfn_cnt;
    dfn_node[dfn_cnt] = 1;
    sub_size[1] = 1;
    depth[1] = 1;
    fa[1][0] = 0;
    root_path[1] = trie_insert(0, val[1]);

    while (stk_top > 0) {
        int u = stk[stk_top].u;
        int f = stk[stk_top].f;
        int e = stk[stk_top].e;

        if (e == 0) {   // 所有边处理完：离开 u，把子树大小合并给父
            if (f != 0) sub_size[f] += sub_size[u];
            stk_top--;
            continue;
        }

        stk[stk_top].e = nxt[e];   // 取走当前边
        int v = to[e];
        if (v == f) continue;

        // 进入子节点 v
        stk_top++;
        stk[stk_top] = {v, u, head[v]};
        dfn[v] = ++dfn_cnt;
        dfn_node[dfn_cnt] = v;
        sub_size[v] = 1;
        depth[v] = depth[u] + 1;
        fa[v][0] = u;
        for (int k = 1; k <= 17; k++)
            fa[v][k] = fa[fa[v][k - 1]][k - 1];
        root_path[v] = trie_insert(root_path[u], val[v]);
    }
}

// 倍增求 LCA
int lca(int x, int y) {
    if (depth[x] < depth[y]) swap(x, y);
    for (int k = 17; k >= 0; k--)
        if (depth[fa[x][k]] >= depth[y]) x = fa[x][k];
    if (x == y) return x;
    for (int k = 17; k >= 0; k--)
        if (fa[x][k] != fa[y][k]) {
            x = fa[x][k];
            y = fa[y][k];
        }
    return fa[x][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) cin >> val[i];
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }

    dfs1();   // 版本 0（tot=0）表示空 Trie，root_path[0] = 0

    // 按 dfn 序建"子树版本"的 Trie
    for (int i = 1; i <= n; i++)
        root_dfn[i] = trie_insert(root_dfn[i - 1], val[dfn_node[i]]);

    for (int t = 0; t < q; t++) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, z;
            cin >> x >> z;
            int l = dfn[x], r = dfn[x] + sub_size[x] - 1;   // 子树对应 dfn 区间
            cout << trie_query_interval(root_dfn[l - 1], root_dfn[r], z) << '\n';
        } else {
            int x, y, z;
            cin >> x >> y >> z;
            int w = lca(x, y);
            // 路径 = (根到 x) + (根到 y) - (根到 lca) - (根到 fa[lca])
            cout << trie_query_path(root_path[x], root_path[y],
                                    root_path[w], root_path[fa[w][0]], z) << '\n';
        }
    }

    return 0;
}
