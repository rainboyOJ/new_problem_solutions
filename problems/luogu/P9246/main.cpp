/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 11:50
 * update_at: 2026-10-03 11:50
 */
// P9246 [蓝桥杯 2023 省 B] 砍树
// 思路：
//   1. 砍掉一条边以后树只剩两个连通块，所以一对 (a, b) 被砍开的充要条件是
//      “这条边在 a 到 b 的树上路径上”。于是每条边只需要一个信息：
//      有多少条给定路径跨过它；被全部 m 条路径跨过的边才是可行答案。
//   2. 砍掉边 (u, par[u]) 会把树分成 u 的子树和子树外两部分，
//      跨过它的路径数 cross[u] 恰好等于“子树内标记和”，用点差分一次求出：
//      对每条路径 (a, b) 做 diff[a] += 1、diff[b] += 1、diff[lca(a,b)] -= 2，
//      自底向上把子树内的标记加起来就是 cross[u]。
//   3. LCA 用倍增求；自底向上求和用 bfs 序倒扫代替递归，避免链状数据爆栈。
//   4. 按输入顺序扫一遍所有边，cross == m 就更新答案，最后留下的自然是最大编号。
#include <iostream>
using namespace std;

const int MAXN = 100005;
const int MAXE = 200005;
const int LOG = 18; // 2^17 > 1e5，足够表示任意深度差

int n, m;

int head[MAXN], nxt[MAXE], to[MAXE], ecnt; // 链式前向星存树
int eu[MAXN], ev[MAXN];                    // 第 i 条输入边的两个端点

int par[MAXN];          // par[u]：以 1 为根时 u 的父亲
int dep[MAXN];          // dep[u]：u 的深度，根的深度为 1
int ord[MAXN], ordcnt;  // bfs 序，父亲一定排在儿子前面
int up[LOG][MAXN];      // up[j][u]：u 的第 2^j 级祖先，倍增求 LCA
int diff[MAXN];         // 点差分标记：路径端点 +1、LCA -2
int cross_[MAXN];       // cross_[u]：跨过 (u, par[u]) 这条边的路径条数

// 加一条无向边
void add_edge(int u, int v) {
    ecnt++;
    to[ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt;
    ecnt++;
    to[ecnt] = u;
    nxt[ecnt] = head[v];
    head[v] = ecnt;
}

// 以 1 为根，用迭代 bfs 求父亲、深度、bfs 序，并建好倍增表。
// 不用递归 dfs 是因为 n 可以达到 1e5，链状数据会爆系统栈。
void build_tree() {
    int qh = 0, qt = 0;
    par[1] = 0;
    dep[1] = 1;
    ord[qt++] = 1;
    while (qh < qt) {
        int u = ord[qh++];
        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (v == par[u]) continue; // 树上除父亲外的邻居都是儿子
            par[v] = u;
            dep[v] = dep[u] + 1;
            ord[qt++] = v;
        }
    }
    ordcnt = qt;
    for (int v = 1; v <= n; v++) up[0][v] = par[v];
    // bfs 序保证父亲先于儿子，逐层递推即可
    for (int j = 1; j < LOG; j++) {
        for (int k = 0; k < ordcnt; k++) {
            int v = ord[k];
            up[j][v] = up[j - 1][up[j - 1][v]];
        }
    }
}

// 倍增求 LCA
int lca(int u, int v) {
    if (dep[u] < dep[v]) {
        int t = u;
        u = v;
        v = t;
    }
    int d = dep[u] - dep[v];
    for (int j = 0; j < LOG; j++) {
        if ((d >> j) & 1) u = up[j][u];
    }
    if (u == v) return u;
    for (int j = LOG - 1; j >= 0; j--) {
        if (up[j][u] != up[j][v]) {
            u = up[j][u];
            v = up[j][v];
        }
    }
    return up[0][u];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n - 1; i++) {
        cin >> eu[i] >> ev[i];
        add_edge(eu[i], ev[i]);
    }

    build_tree();

    // 读入 m 个数对，直接打成点差分标记
    for (int i = 1; i <= m; i++) {
        int a, b;
        cin >> a >> b;
        int w = lca(a, b);
        diff[a]++;
        diff[b]++;
        diff[w] -= 2;
    }

    // 逆 bfs 序累加子树标记：处理到 u 时，它的儿子都已经把值推给了 u
    for (int k = ordcnt - 1; k >= 0; k--) {
        int u = ord[k];
        cross_[u] = diff[u];
        if (u != 1) diff[par[u]] += diff[u];
    }

    // 依次检查每条边，编号递增所以最后记下的就是最大编号
    int ans = -1;
    for (int i = 1; i <= n - 1; i++) {
        int u = eu[i], v = ev[i];
        int child; // 这条边在 bfs 树上的儿子端点
        if (par[u] == v) {
            child = u;
        } else {
            child = v;
        }
        if (cross_[child] == m) ans = i;
    }

    cout << ans << '\n';
    return 0;
}
