/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-21 03:09
 * update_at: 2026-10-29 16:26
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 树链剖分（HLD）+ 线段树（区间和 + 区间最大值），节点与区间均为 1 下标。
// 参考 rbook 模板 hld 的全局数组 + 普通函数写法。
// 本题特点：
//   - 不取模
//   - 只有单点修改（CHANGE），线段树不需要懒标记
//   - 同时维护区间和与区间最大值
//   - 点权可为负，查询最大值时必须用足够小的初值

const int maxn = 30000 + 5;
const ll NEG_INF = -(1LL << 60); // 点权可能为负，路径最大值查询的初值

int n;

/*------------------------ sgt 代码 开始 ------------------------*/
// 线段树：维护数组 base[1..n]，支持单点修改、区间和、区间最大值。
ll base[maxn];
ll tr[maxn << 2]; // 区间和
ll mx[maxn << 2]; // 区间最大值

int ls(int p) { return p << 1; }
int rs(int p) { return p << 1 | 1; }

// 用左右儿子的信息更新 p
void push_up(int p) {
    tr[p] = tr[ls(p)] + tr[rs(p)];
    mx[p] = max(mx[ls(p)], mx[rs(p)]);
}

void seg_build(int p, int l, int r) {
    if (l == r) {
        tr[p] = base[l];
        mx[p] = base[l];
        return;
    }
    int mid = (l + r) >> 1;
    seg_build(ls(p), l, mid);
    seg_build(rs(p), mid + 1, r);
    push_up(p);
}

// 单点修改：把 dfn 位置 pos 的值改为 value
void point_update(int pos, ll value, int p, int l, int r) {
    if (l == r) {
        tr[p] = value;
        mx[p] = value;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) point_update(pos, value, ls(p), l, mid);
    else point_update(pos, value, rs(p), mid + 1, r);
    push_up(p);
}

// 区间和
ll range_sum(int ql, int qr, int p, int l, int r) {
    if (qr < l || r < ql) return 0;
    if (ql <= l && r <= qr) return tr[p];
    int mid = (l + r) >> 1;
    ll answer = range_sum(ql, qr, ls(p), l, mid);
    answer += range_sum(ql, qr, rs(p), mid + 1, r);
    return answer;
}

// 区间最大值（不相交返回 NEG_INF）
ll range_max(int ql, int qr, int p, int l, int r) {
    if (qr < l || r < ql) return NEG_INF;
    if (ql <= l && r <= qr) return mx[p];
    int mid = (l + r) >> 1;
    ll answer = range_max(ql, qr, ls(p), l, mid);
    answer = max(answer, range_max(ql, qr, rs(p), mid + 1, r));
    return answer;
}
/*------------------------ sgt 代码 结束 ------------------------*/

/*------------------------ hld 代码 开始 ------------------------*/
// 树链剖分：g 存树，a 存原点权，6 个核心数组维护树上信息。
vector<int> g[maxn];
ll a[maxn];

int fa[maxn];  // fa[u]：父亲，根的 fa 为 0
int dep[maxn]; // dep[u]：深度，根为 1
int sz[maxn];  // sz[u]：子树大小（含自己）
int son[maxn]; // son[u]：重儿子，叶子为 0
int top[maxn]; // top[u]：所在重链的链头
int dfn[maxn]; // dfn[u]：线段树上的位置（DFS 新编号）
int timer;

void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

// 第一遍 DFS：往下求 fa、dep，回溯时汇总 sz 并选出重儿子 son
void dfs1(int u, int father) {
    fa[u] = father;
    dep[u] = dep[father] + 1; // 根的 father 为 0、dep[0] 恒为 0，故根深度为 1
    sz[u] = 1;                // 先算上自己
    son[u] = 0;               // 叶子没有重儿子
    for (int v : g[u]) {
        if (v == father) continue;
        dfs1(v, u);
        sz[u] += sz[v];
        if (sz[v] > sz[son[u]]) son[u] = v;
    }
}

// 第二遍 DFS：重儿子优先分配 dfn，保证重链连续
void dfs2(int u, int head) {
    top[u] = head;
    dfn[u] = ++timer;
    base[timer] = a[u]; // 把点权搬到 sgt 段的数组上，线段树维护的就是它
    if (son[u]) dfs2(son[u], head);
    for (int v : g[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

// 预处理入口：加完边之后调用一次。其余数组在 dfs1 / dfs2 / seg_build 里逐点覆写。
void build(int root) {
    dfs1(root, 0);      // 填 fa / dep / sz / son
    timer = 0;          // 从 1 重新分配 dfn
    dfs2(root, root);   // 填 top / dfn / base
    seg_build(1, 1, n); // 交给 sgt 段
}

// 路径 (u, v) 上所有点的和。
// 不在同一条重链时，处理“链头更深”那一侧的整段 [dfn[top[u]], dfn[u]]，
// 然后 u 跳到链头的父亲。每条轻边都让子树大小至少翻倍，所以最多跳 O(log n) 次。
ll path_sum(int u, int v) {
    ll answer = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        answer += range_sum(dfn[top[u]], dfn[u], 1, 1, n);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    answer += range_sum(dfn[u], dfn[v], 1, 1, n);
    return answer;
}

// 路径 (u, v) 上所有点的最大值。跳链过程与 path_sum 完全一致。
ll path_max(int u, int v) {
    ll answer = NEG_INF;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        answer = max(answer, range_max(dfn[top[u]], dfn[u], 1, 1, n));
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    answer = max(answer, range_max(dfn[u], dfn[v], 1, 1, n));
    return answer;
}
/*------------------------ hld 代码 结束 ------------------------*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    for (int u = 1; u <= n; ++u) g[u].clear();

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    build(1); // 根固定为 1

    int q;
    cin >> q;
    while (q--) {
        string op;
        int u, v;
        cin >> op >> u >> v;

        if (op[1] == 'H') {
            // CHANGE u t : 单点修改
            a[u] = v;
            point_update(dfn[u], v, 1, 1, n);
        } else if (op[1] == 'M') {
            // QMAX u v
            cout << path_max(u, v) << '\n';
        } else {
            // QSUM u v
            cout << path_sum(u, v) << '\n';
        }
    }

    return 0;
}
