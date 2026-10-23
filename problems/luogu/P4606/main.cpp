/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 13:36
 * update_at: 2026-10-23 14:12
 */
// 圆方树 + 虚树路径计数。
// 圆方树深度最大约 2n（链图），实测判题器 64MB 栈下递归安全，故 Tarjan 与圆方树遍历直接递归。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 100000 + 5; // 原图圆点数量上限
const int MAXM = 200000 + 5; // 原图边数上限
const int MAXV = 300005;     // 圆方树节点上限：n 个圆点 + 至多 m 个方点
const int MAXLOG = 20;       // 3e5 < 2^19，20 层足够让倍增 LCA 爬到根

int n, m, q;

// 原图：链式前向星。边编号从 0 开始成对分配，e^1 就是它的反向边。
int head[MAXN], to[MAXM * 2], nxt[MAXM * 2], edge_cnt;

// Tarjan 求点双：时间戳、点栈（尚未归属任何点双的点）
int dfn[MAXN], low[MAXN], dfs_clock;
int node_stack[MAXN], stack_top;

int square_cnt;           // 方点个数，方点编号为 n+1 .. n+square_cnt
int total_node;           // 圆方树节点总数 = n + square_cnt
vector<int> tree[MAXV];   // 圆方树邻接表，圆点 1..n，方点 n+1..

// 圆方树上的预处理信息
int tin[MAXV];        // 圆方树的 DFS 序，用来给询问点集排序
int depth[MAXV];      // 圆方树上的深度（边数），供 LCA 使用
int pre_circle[MAXV]; // pre_circle[x]：根到 x 的路径上（含根、含 x）的圆点个数
int up[MAXLOG][MAXV]; // 倍增祖先，up[0][x] 是 x 的父节点，0 表示不存在
int tree_clock;       // 圆方树 DFS 序计数器

// 输入只有非负整数，用 getchar 手写快读，避免多组大数据下 cin 太慢。
int read_int() {
    int c = getchar();
    while (c < '0' || c > '9') {
        c = getchar();
    }
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar();
    }
    return x;
}

void add_edge(int u, int v) {
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
    edge_cnt++;
}

// 把「点栈顶弹到 u（含），再并上割点 p」的这些点连到一个新建的方点上。
void add_square(int u, int p) {
    square_cnt++;
    int sq = n + square_cnt;
    tree[sq].push_back(p);
    tree[p].push_back(sq);
    while (true) {
        int x = node_stack[stack_top--];
        tree[sq].push_back(x);
        tree[x].push_back(sq);
        if (x == u) {
            break;
        }
    }
}

// Tarjan 求点双并同时建出圆方树。
// 回溯到 u 时若 low[u] >= dfn[p]（p 为 u 的父亲），说明 u 的子树回不到 p 的上面，
// 此时点栈顶弹到 u（含）、再并上 p，就组成一个点双，连到一个新建的方点上。
// 根节点的点双都已在某个儿子的回溯里弹出，返回时把残留在点栈底部的根弹掉即可。
void tarjan(int u, int in_edge) {
    dfn[u] = low[u] = ++dfs_clock;
    node_stack[++stack_top] = u;

    for (int e = head[u]; e != -1; e = nxt[e]) {
        int v = to[e];

        // 只跳过进入 u 的那条边本身，重边必须保留（两条平行边构成一个点双）。
        if (e == (in_edge ^ 1)) {
            continue;
        }

        if (!dfn[v]) {
            tarjan(v, e);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) {
                add_square(v, u);
            }
        }
        // 返祖边只能用祖先的 dfn 更新 low。
        else if (dfn[v] < dfn[u]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

// 圆方树遍历：一趟求出 DFS 序、深度、圆点前缀和、倍增父亲。
void dfs_tree(int u, int p) {
    tin[u] = ++tree_clock;
    up[0][u] = p;
    for (auto v : tree[u]) {
        if (v == p) {
            continue;
        }
        depth[v] = depth[u] + 1;
        // 方点权值为 0，不计入圆点前缀和
        pre_circle[v] = pre_circle[u] + (v <= n ? 1 : 0);
        dfs_tree(v, u);
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }
    int diff = depth[u] - depth[v];
    for (int j = 0; j < MAXLOG; j++) {
        if ((diff >> j) & 1) {
            u = up[j][u];
        }
    }
    if (u == v) {
        return u;
    }
    for (int j = MAXLOG - 1; j >= 0; j--) {
        if (up[j][u] != up[j][v]) {
            u = up[j][u];
            v = up[j][v];
        }
    }
    return up[0][u];
}

int ask_points[MAXN]; // 当前询问给出的点集，按圆方树 DFS 序排序后用

bool cmp_by_tin(int a, int b) {
    return tin[a] < tin[b];
}

void solve_one_case() {
    n = read_int();
    m = read_int();

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        dfn[i] = 0;
        low[i] = 0;
    }
    edge_cnt = 0;
    dfs_clock = 0;
    stack_top = 0;

    for (int i = 1; i <= m; i++) {
        int u = read_int();
        int v = read_int();
        add_edge(u, v);
        add_edge(v, u);
    }

    square_cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!dfn[i]) {
            stack_top = 0;
            tarjan(i, -1);
            stack_top--; // 根节点残留在点栈底部，弹掉
        }
    }
    total_node = n + square_cnt;

    tree_clock = 0;
    for (int i = 1; i <= total_node; i++) {
        tin[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        if (!tin[i]) {
            depth[i] = 0;
            pre_circle[i] = 1; // 根一定取圆点，它自己算一个圆点
            dfs_tree(i, 0);
        }
    }

    for (int j = 1; j < MAXLOG; j++) {
        for (int v = 1; v <= total_node; v++) {
            up[j][v] = up[j - 1][up[j - 1][v]];
        }
    }

    q = read_int();
    for (int i = 1; i <= q; i++) {
        int k = read_int();
        for (int j = 0; j < k; j++) {
            ask_points[j] = read_int();
        }
        sort(ask_points, ask_points + k, cmp_by_tin);

        // 环巡游：把 S 按 DFS 序首尾相接，相邻两点距离之和等于
        // 极小连通子树的边权和的两倍。边权定义成「儿子的点权」，
        // 于是边权和 = 子树内圆点数 - 子树根的权值。
        ll sum_dist = 0;
        for (int j = 0; j < k; j++) {
            int u = ask_points[j];
            int v = ask_points[(j + 1) % k];
            int w = lca(u, v);
            sum_dist += pre_circle[u] + pre_circle[v] - 2 * pre_circle[w];
        }

        // S 的虚树根 = DFS 序最小与最大两点的 LCA
        int root_of_tree = lca(ask_points[0], ask_points[k - 1]);
        ll circle_cnt = sum_dist / 2 + (root_of_tree <= n ? 1 : 0);

        // 答案 = 虚树上的圆点数 - |S|（S 自身的点不可能是被摧毁的城市）
        printf("%lld\n", circle_cnt - k);
    }

    // 多组数据之间清空圆方树，避免与下一组混淆
    for (int i = 1; i <= total_node; i++) {
        tree[i].clear();
    }
}

int main() {
    int T = read_int();
    for (int tc = 1; tc <= T; tc++) {
        solve_one_case();
    }
    return 0;
}
