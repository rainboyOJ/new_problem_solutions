/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:29
 * update_at: 2026-10-29 16:05
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ===================== 重链剖分 + 懒标记线段树 =====================
// 骨架取自 rbook 模板 hld：全部是全局数组加普通函数，没有 struct/class。
// 模板把代码分成两段：sgt 段只管数组 base[1..n] 上的区间加/区间和，
// hld 段负责把树上路径与子树翻译成 base 上的连续区间。
// 使用顺序：直接读 n / mod -> 读点权到 a[] -> add_edge 加边 -> build(root) -> 操作。
// 节点编号、dfn 编号、线段树下标全部 1 起。

const int maxn = 100000 + 5; // 本题 n <= 1e5。模板要求 n <= maxn，不能越界

int n, mod; // n：节点数；mod：题目给的取模数 P，所有输出都对它取模

/*------------------------ sgt 代码 开始 ------------------------*/
// 懒标记线段树：维护数组 base[1..n]，支持区间加、区间和对 mod 取模。
ll base[maxn];        // base[t]：按 dfn 重排后的点权，线段树就建在它上面
ll tr[maxn << 2];     // tr[p]：节点 p 覆盖区间的和（已取模）
ll lazy[maxn << 2];   // lazy[p]：节点 p 上欠着、还没下发的“整段加”的值

// 把可能为负的 x 归一到 [0, mod)：只用在“外来值”上（输入的初值和增量）。
ll norm(ll x) { return (x % mod + mod) % mod; }

int ls(int p) { return p << 1; }     // p 的左儿子 2p
int rs(int p) { return p << 1 | 1; } // p 的右儿子 2p+1

// 给节点 p 的整段区间加 value：区间和增加 value * 长度，懒标记也累加 value。
// 这样整段加可以在节点摘要上 O(1) 结算，不必下到叶子。
void apply(int p, int l, int r, ll value) {
    value = norm(value);
    tr[p] = (tr[p] + value * (r - l + 1)) % mod;
    lazy[p] = (lazy[p] + value) % mod;
}

void pushdown(int p, int l, int r) {
    // 懒标记为 0 无事可做；叶子没有儿子可下放，必须提前返回，
    // 否则 mid = l，会递归进入自己并且写越界的 tr[2p]。
    if (!lazy[p] || l == r) return;
    int mid = (l + r) >> 1;
    apply(ls(p), l, mid, lazy[p]);
    apply(rs(p), mid + 1, r, lazy[p]);
    lazy[p] = 0;
}

// 用 base[1..n] 建树。入口顺手清掉 lazy[p]：这样就不必整体清零 lazy 数组。
void seg_build(int p, int l, int r) {
    lazy[p] = 0;
    if (l == r) {
        tr[p] = norm(base[l]);
        return;
    }
    int mid = (l + r) >> 1;
    seg_build(ls(p), l, mid);
    seg_build(rs(p), mid + 1, r);
    tr[p] = (tr[ls(p)] + tr[rs(p)]) % mod;
}

// 区间加：把 [ql, qr] 整体加 value。
// 四分式：先剪掉完全不相交的分支，再处理完全包含的分支，最后才递归两侧。
void range_add(int ql, int qr, ll value, int p, int l, int r) {
    if (qr < l || r < ql) return; // 不相交，剪掉
    if (ql <= l && r <= qr) {     // 完全包含，整段打标记
        apply(p, l, r, value);
        return;
    }
    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    range_add(ql, qr, value, ls(p), l, mid);
    range_add(ql, qr, value, rs(p), mid + 1, r);
    tr[p] = (tr[ls(p)] + tr[rs(p)]) % mod;
}

// 区间和：与 range_add 同一副骨架，只是“不相交”返回 0、“完全包含”返回摘要。
ll range_sum(int ql, int qr, int p, int l, int r) {
    if (qr < l || r < ql) return 0;      // 不相交
    if (ql <= l && r <= qr) return tr[p]; // 完全包含
    pushdown(p, l, r);
    int mid = (l + r) >> 1;
    ll answer = range_sum(ql, qr, ls(p), l, mid);
    answer += range_sum(ql, qr, rs(p), mid + 1, r);
    return answer % mod;
}
/*------------------------ sgt 代码 结束 ------------------------*/

/*------------------------ hld 代码 开始 ------------------------*/
// 树链剖分：g 存树，a 存原点权，6 个核心数组维护树上信息。
vector<int> g[maxn]; // g[u]：u 的邻接表（无向树，两边都存）
ll a[maxn];          // a[u]：原树上的点权

int fa[maxn];  // fa[u]：父亲，根的 fa 为 0
int dep[maxn]; // dep[u]：深度，根为 1
int sz[maxn];  // sz[u]：子树大小（含自己）
int son[maxn]; // son[u]：重儿子，叶子为 0
int top[maxn]; // top[u]：所在重链的链头
int dfn[maxn]; // dfn[u]：线段树上的位置（DFS 新编号）
int timer;     // dfn 计数器

void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

// 第一遍 DFS：往下求 fa、dep，回溯时汇总 sz 并选出重儿子 son。
// 重儿子 = 子树最大的儿子；用 sz[son[u]] 比较，sz[0] 恒为 0 顺带处理了“还没有重儿子”。
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

// 第二遍 DFS：重儿子优先分配 dfn，保证整条重链的编号连续。
// 每个轻儿子自己开一条新链，所以传进去的链头就是它自己。
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

// 预处理入口：加完边之后调用一次。其余数组在 dfs1 / dfs2 / seg_build 里逐点覆写，
// 所以不需要事先清零。sz[u] 必须在 dfs2 之前算好，因为子树区间
// [dfn[u], dfn[u] + sz[u] - 1] 依赖它。
void build(int root) {
    dfs1(root, 0);      // 填 fa / dep / sz / son
    timer = 0;          // 从 1 重新分配 dfn
    dfs2(root, root);   // 填 top / dfn / base
    seg_build(1, 1, n); // 交给 sgt 段
}

// 只跳链求 LCA，O(log n)。本题用不到，保留是因为它和路径操作同构。
int lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}

// 路径 (u, v) 上所有点加 delta。
// 不在同一条重链时，处理“链头更深”那一侧的整段 [dfn[top[u]], dfn[u]]，
// 然后 u 跳到链头的父亲，即跨过一条轻边。每条轻边都让子树大小至少翻倍，
// 所以最多跳 O(log n) 次。两侧链头相同时，剩下的就是同一条链上的一段区间。
void path_add(int u, int v, ll delta) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        range_add(dfn[top[u]], dfn[u], delta, 1, 1, n);
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    range_add(dfn[u], dfn[v], delta, 1, 1, n);
}

// 路径 (u, v) 上所有点的和。跳链过程与 path_add 完全一致。
ll path_sum(int u, int v) {
    ll answer = 0;
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]]) swap(u, v);
        answer = (answer + range_sum(dfn[top[u]], dfn[u], 1, 1, n)) % mod;
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    answer = (answer + range_sum(dfn[u], dfn[v], 1, 1, n)) % mod;
    return answer;
}

// 子树操作不需要跳链：以 u 为根的子树在 dfn 上正好是连续区间
// [dfn[u], dfn[u] + sz[u] - 1]，一次区间操作即可。
void subtree_add(int u, ll delta) {
    range_add(dfn[u], dfn[u] + sz[u] - 1, delta, 1, 1, n);
}

ll subtree_sum(int u) {
    return range_sum(dfn[u], dfn[u] + sz[u] - 1, 1, 1, n);
}
/*------------------------ hld 代码 结束 ------------------------*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, root;                  // 操作数、根
    cin >> n >> m >> root >> mod; // 点数和模数直接读进全局

    for (int u = 1; u <= n; ++u) g[u].clear(); // 清掉上一组留下的边

    for (int i = 1; i <= n; i++) cin >> a[i]; // 原编号下的点权，取模在 seg_build 里做

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }

    build(root); // 两遍 DFS + 建线段树

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, y;
            ll z;
            cin >> x >> y >> z;
            path_add(x, y, z);
        } else if (op == 2) {
            int x, y;
            cin >> x >> y;
            cout << path_sum(x, y) << '\n';
        } else if (op == 3) {
            int x;
            ll z;
            cin >> x >> z;
            subtree_add(x, z);
        } else {
            int x;
            cin >> x;
            cout << subtree_sum(x) << '\n';
        }
    }

    return 0;
}
