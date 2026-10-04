/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:27
 * update_at: 2026-10-05 03:27
 */
// 树上最长异或路径：d[u] = 根到 u 的边权异或和，则 u->v 路径异或 = d[u]^d[v]，
// 问题变成 n 个数里求最大异或对，用 01 字典树逐位贪心，O(31n)。

#include <cstdio>

typedef long long ll;

const int MAXN = 100005;      // 点数上限
const int MAXNODE = MAXN * 32; // 字典树结点数上界：1 + 31n
const int BITS = 31;          // 边权 < 2^31，字典树走 31 层（第 30 位到第 0 位）

// 链式前向星存树
int head[MAXN], nxt[2 * MAXN], to[2 * MAXN], wei[2 * MAXN];
int cnt_edge = 0;

int n;
ll d[MAXN];        // d[u]：根到 u 的路径边权异或和
bool vis[MAXN];    // 迭代 DFS 时标记点是否入过栈

int ch[MAXNODE][2]; // ch[u][b]：结点 u 的第 b 位孩子下标，0 表示空
int node_num = 0;   // 已用结点数，0 号为根

ll ans = 0;

// 加一条无向边
void add_edge(int u, int v, int w) {
    cnt_edge++;
    to[cnt_edge] = v;
    wei[cnt_edge] = w;
    nxt[cnt_edge] = head[u];
    head[u] = cnt_edge;
}

// 迭代 DFS 求根到每个点的边权异或和（树可能退化成链，避免递归爆栈）
void dfs_d() {
    // 栈里依次放：点、父点、累计异或和
    static int stk_node[MAXN], stk_fa[MAXN];
    static ll stk_xor[MAXN];
    int top = 1;
    stk_node[1] = 1;
    stk_fa[1] = 0;
    stk_xor[1] = 0;
    vis[1] = true;
    d[1] = 0;
    while (top > 0) {
        int u = stk_node[top];
        int fa = stk_fa[top];
        ll acc = stk_xor[top];
        top--;
        d[u] = acc;
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (v == fa) continue;
            if (vis[v]) continue; // 父点之外的重复保护（树本来无环，双保险）
            vis[v] = true;
            top++;
            stk_node[top] = v;
            stk_fa[top] = u;
            stk_xor[top] = acc ^ wei[e];
        }
    }
}

// 把 x 按高位到低位插入 01 字典树
void trie_insert(ll x) {
    int u = 0;
    for (int b = BITS - 1; b >= 0; b--) {
        int bit = (x >> b) & 1;
        if (ch[u][bit] == 0) {
            node_num++;
            ch[node_num][0] = ch[node_num][1] = 0;
            ch[u][bit] = node_num;
        }
        u = ch[u][bit];
    }
}

// 在字典树里逐位贪心：能走"与 x 这一位相反"的分支就走，本位异或得 1，
// 高位收益大于所有低位之和，所以这样取一定最优；返回与 x 异或的最大值
ll trie_max_xor(ll x) {
    int u = 0;
    ll res = 0;
    for (int b = BITS - 1; b >= 0; b--) {
        int bit = (x >> b) & 1;
        if (ch[u][1 - bit] != 0) {
            res |= 1LL << b;
            u = ch[u][1 - bit];
        } else {
            u = ch[u][bit];
        }
    }
    return res;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    dfs_d();

    // 先插后查：允许 x 与自己配对（异或为 0），不影响最大值，还保证树非空
    for (int i = 1; i <= n; i++) {
        trie_insert(d[i]);
        ll cur = trie_max_xor(d[i]);
        if (cur > ans) ans = cur;
    }

    printf("%lld\n", ans);
    return 0;
}
