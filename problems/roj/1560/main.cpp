/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:18
 * update_at: 2026-10-05 08:18
 */

// 树链剖分（重链剖分）+ 线段树，维护单点修改、路径最大值、路径和。
// 核心思想：优先遍历重儿子，使每条重链在 DFS 序上对应一段连续区间，
// 于是树上路径可拆成 O(log n) 段区间，交给线段树做单点改、区间查。

#include <cstdio>
#include <algorithm>

typedef long long ll;

const int MAXN = 30005;      // 节点数上限（n <= 3e4）
const ll  INF = 1e9;         // 权值绝对值 <= 30000，用 1e9 做无穷大足够

int n, q;
ll weight[MAXN];             // weight[u] = 节点 u 的点权

// 链式前向星存树
int head[MAXN], nxt[2 * MAXN], to[2 * MAXN], edge_cnt;
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// 树链剖分信息
int parent[MAXN];            // 父节点
int depth[MAXN];             // 深度，根为 1
int heavy[MAXN];             // 重儿子编号，叶子为 0
int top_[MAXN];              // 所在重链的链顶
int dfn[MAXN];               // DFS 序编号，同一条重链上的 dfn 连续
int timer_cnt;

// 线段树（按 dfn 序建）：sum 区间和，mx 区间最大值
ll sum_tree[4 * MAXN];
ll mx_tree[4 * MAXN];

// ---- 第一次遍历：求 parent、depth、size，并选重儿子 ----
// 用非递归的栈式 DFS，避免 n 较大时递归爆栈；order 保存遍历顺序供倒序算子树大小
int sta[MAXN], order[MAXN], size_[MAXN];
void dfs1(int root) {
    int top = 0, cnt = 0;
    sta[++top] = root;
    parent[root] = 0;
    depth[root] = 1;
    while (top > 0) {
        int u = sta[top];
        top--;
        cnt++;
        order[cnt] = u;
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (v == parent[u]) continue;
            parent[v] = u;
            depth[v] = depth[u] + 1;
            sta[++top] = v;
        }
    }
    // 倒序回溯：孩子一定先于父亲入过栈，倒序累加子树大小并选重儿子
    for (int i = cnt; i >= 1; i--) {
        int u = order[i];
        size_[u] = 1;
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (v == parent[u]) continue;
            size_[u] += size_[v];
            if (size_[v] > size_[heavy[u]]) heavy[u] = v;
        }
    }
}

// ---- 第二次遍历：优先走重儿子，求 dfn 和 top ----
void dfs2(int root) {
    // 栈里存 (节点, 链顶)，重儿子后压栈从而先被访问
    int top = 0;
    static int node_st[2 * MAXN];
    static int top_st[2 * MAXN];
    node_st[++top] = root;
    top_st[top] = root;
    while (top > 0) {
        int u = node_st[top];
        int t = top_st[top];
        top--;
        timer_cnt++;
        dfn[u] = timer_cnt;
        top_[u] = t;
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (v == parent[u] || v == heavy[u]) continue;
            top++;
            node_st[top] = v;
            top_st[top] = v;   // 轻儿子自成一条新链，链顶是它自己
        }
        if (heavy[u] != 0) {
            top++;
            node_st[top] = heavy[u];
            top_st[top] = t;   // 重儿子继承当前链顶
        }
    }
}

// ---- 线段树 ----
// 建树：pos 是 dfn 位置，叶子权值按 dfn 序排布
ll seg_val[MAXN];            // seg_val[dfn[u]] = dfn 序位置上的点权
void build(int node, int l, int r) {
    if (l == r) {
        sum_tree[node] = seg_val[l];
        mx_tree[node] = seg_val[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(node << 1, l, mid);
    build(node << 1 | 1, mid + 1, r);
    sum_tree[node] = sum_tree[node << 1] + sum_tree[node << 1 | 1];
    mx_tree[node] = std::max(mx_tree[node << 1], mx_tree[node << 1 | 1]);
}

// 单点修改：把位置 pos 的值改为 val
void update(int node, int l, int r, int pos, ll val) {
    if (l == r) {
        sum_tree[node] = val;
        mx_tree[node] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) update(node << 1, l, mid, pos, val);
    else update(node << 1 | 1, mid + 1, r, pos, val);
    sum_tree[node] = sum_tree[node << 1] + sum_tree[node << 1 | 1];
    mx_tree[node] = std::max(mx_tree[node << 1], mx_tree[node << 1 | 1]);
}

ll query_sum(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return sum_tree[node];
    int mid = (l + r) >> 1;
    ll res = 0;
    if (ql <= mid) res += query_sum(node << 1, l, mid, ql, qr);
    if (qr > mid) res += query_sum(node << 1 | 1, mid + 1, r, ql, qr);
    return res;
}

ll query_max(int node, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return mx_tree[node];
    int mid = (l + r) >> 1;
    ll res = -INF;
    if (ql <= mid) res = std::max(res, query_max(node << 1, l, mid, ql, qr));
    if (qr > mid) res = std::max(res, query_max(node << 1 | 1, mid + 1, r, ql, qr));
    return res;
}

// 树上路径拆链：每次跳链顶较深的一端，查 [dfn[top[u]], dfn[u]]，最后查同链一段
ll path_sum(int u, int v) {
    ll res = 0;
    while (top_[u] != top_[v]) {
        if (depth[top_[u]] < depth[top_[v]]) std::swap(u, v);
        res += query_sum(1, 1, n, dfn[top_[u]], dfn[u]);
        u = parent[top_[u]];
    }
    if (depth[u] > depth[v]) std::swap(u, v);
    res += query_sum(1, 1, n, dfn[u], dfn[v]);
    return res;
}

ll path_max(int u, int v) {
    ll res = -INF;
    while (top_[u] != top_[v]) {
        if (depth[top_[u]] < depth[top_[v]]) std::swap(u, v);
        res = std::max(res, query_max(1, 1, n, dfn[top_[u]], dfn[u]));
        u = parent[top_[u]];
    }
    if (depth[u] > depth[v]) std::swap(u, v);
    res = std::max(res, query_max(1, 1, n, dfn[u], dfn[v]));
    return res;
}

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        add_edge(b, a);
    }
    for (int i = 1; i <= n; i++) scanf("%lld", &weight[i]);

    dfs1(1);
    dfs2(1);
    for (int u = 1; u <= n; u++) seg_val[dfn[u]] = weight[u]; // 按 dfn 序排布点权
    build(1, 1, n);

    scanf("%d", &q);
    char op[10];
    for (int i = 1; i <= q; i++) {
        scanf("%s", op);
        int a, b;
        scanf("%d %d", &a, &b);
        if (op[0] == 'C') {
            update(1, 1, n, dfn[a], b);   // CHANGE：改 dfn[a] 位置的值
        } else if (op[1] == 'M') {
            printf("%lld\n", path_max(a, b));
        } else {
            printf("%lld\n", path_sum(a, b));
        }
    }
}

int main() {
    solve();
    return 0;
}
