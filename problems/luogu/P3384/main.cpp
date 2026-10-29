/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:29
 * update_at: 2026-10-29 12:52
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ===================== 重链剖分 + 懒标记线段树 =====================
// 骨架取自 rbook 模板 hld：定长全局数组 + 普通函数，没有 struct/class。
// 使用顺序：init(n, P) -> 读点权到 a[] -> add_edge 加边 -> build(root) -> 四种操作。
// 节点编号、dfn 编号、线段树下标全部 1 起；只在 mod 处取模，其余按 ll 存。

const int maxn = 100000 + 5;  // 本题 n <= 1e5。模板要求 n <= maxn，不能越界

int n;    // 节点个数
int mod;  // 取模数 P，所有输出都对它取模

vector<int> g[maxn];  // g[u]：u 的邻接表（无向树，两边都存）

int fa[maxn];   // fa[u]：父亲，根的 fa 为 0
int dep[maxn];  // dep[u]：深度，根为 1
int sz[maxn];   // sz[u]：子树节点数（含 u 自己）
int son[maxn];  // son[u]：重儿子（子树最大的儿子），叶子为 0
int top[maxn];  // top[u]：u 所在重链的链头
int dfn[maxn];  // dfn[u]：u 在线段树上的位置（DFS 新编号）
int rev[maxn];  // rev[t]：dfn 位置 t 对应的原节点

ll a[maxn];     // a[u]：原树上的点权
ll base[maxn];  // base[t]：按 dfn 重排后的点权，线段树建在它上面
ll tr[maxn << 2];    // tr[u]：线段树节点 u 覆盖区间的和（已取模）
ll lazy[maxn << 2];  // lazy[u]：节点 u 上欠着、还没下发的“整段加”的值

// 把任意整数规整到 [0, mod) 内，保证取模后不会出现负数。
ll norm(ll x) { return (x % mod + mod) % mod; }

// 只清邻接表：旧边必须清掉，否则上一组的边会残留。
// 其余数组不必清零 —— build() 会逐点重写 fa/dep/sz/son/top/dfn/rev/base，
// seg_build() 会重写 tr 并顺手清 lazy，所以旧值影响不到本组结果。
void init(int count, int modulus) {
    n = count;
    mod = modulus;
    for (int u = 1; u <= n; ++u) g[u].clear();
}

void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

// ---------------- 线段树：区间加、区间和 ----------------
// 本题四种操作最终都归结为这两个原语：路径/子树都先变成 dfn 上的连续区间。

// 给节点 u 的整段区间加 value：区间和增加 value * 长度，懒标记也累加 value。
// 这样整段加可以在节点摘要上 O(1) 结算，不必下到叶子。
void apply(int u, int l, int r, ll value) {
    value = norm(value);
    tr[u] = (tr[u] + value * (r - l + 1)) % mod;
    lazy[u] = (lazy[u] + value) % mod;
}

// 把 u 的懒标记推给两个儿子，然后清空 u 的标记。
// l == r 时是叶子，没有儿子可推，直接返回。
void pushdown(int u, int l, int r) {
    if (lazy[u] == 0 || l == r) return;
    int mid = (l + r) >> 1;
    apply(u << 1, l, mid, lazy[u]);
    apply(u << 1 | 1, mid + 1, r, lazy[u]);
    lazy[u] = 0;
}

// 用 base[1..n]（按 dfn 排列好的点权）建树。
// 入口顺手清掉 lazy[u]：这样 init 就不必把整棵 4*maxn 的 lazy 清零。
void seg_build(int u, int l, int r) {
    lazy[u] = 0;
    if (l == r) {
        tr[u] = norm(base[l]);
        return;
    }
    int mid = (l + r) >> 1;
    seg_build(u << 1, l, mid);
    seg_build(u << 1 | 1, mid + 1, r);
    tr[u] = (tr[u << 1] + tr[u << 1 | 1]) % mod;
}

// 区间 [ql, qr] 每个位置加 value。
void range_add(int ql, int qr, ll value, int u, int l, int r) {
    // 当前区间被完全覆盖：整段打标记，不再往下走。
    if (ql <= l && r <= qr) {
        apply(u, l, r, value);
        return;
    }
    pushdown(u, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) range_add(ql, qr, value, u << 1, l, mid);
    if (qr > mid) range_add(ql, qr, value, u << 1 | 1, mid + 1, r);
    tr[u] = (tr[u << 1] + tr[u << 1 | 1]) % mod;
}

// 询问区间 [ql, qr] 的和。
ll range_sum(int ql, int qr, int u, int l, int r) {
    if (ql <= l && r <= qr) return tr[u];
    pushdown(u, l, r);
    int mid = (l + r) >> 1;
    ll answer = 0;
    if (ql <= mid) answer += range_sum(ql, qr, u << 1, l, mid);
    if (qr > mid) answer += range_sum(ql, qr, u << 1 | 1, mid + 1, r);
    return answer % mod;
}

// ---------------- 树链剖分：两遍遍历 + 跳链 ----------------

// 第一遍：先记录“父亲一定排在儿子前面”的顺序，再逆序汇总子树信息。
// 第二遍：显式栈模拟重儿子优先的 DFS，避免链形树上深度 O(n) 的递归。
// order / stk 用静态数组，不每组数据动态分配。
void build(int root) {
    static int order[maxn], stk[maxn];

    // ---- 第一遍正序：定 fa 和 dep ----
    int cnt = 0;
    order[cnt++] = root;
    fa[root] = 0;    // 显式写根的父亲，不依赖 fa 的预清零
    dep[root] = 1;
    for (int i = 0; i < cnt; ++i) {
        int u = order[i];
        for (int v : g[u]) {
            if (v == fa[u]) continue;  // 只认父亲，其余都是儿子
            fa[v] = u;
            dep[v] = dep[u] + 1;
            order[cnt++] = v;
        }
    }

    // ---- 第一遍逆序：汇总 sz，选出重儿子 ----
    // 逆序保证儿子算完再算父亲。用局部变量 best / best_size 比较，
    // 不依赖 son[] 的旧值，所以 init 不需要清 son。
    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        sz[u] = 1;
        son[u] = 0;
        int best = 0, best_size = 0;
        for (int v : g[u]) {
            if (v == fa[u]) continue;
            sz[u] += sz[v];
            if (sz[v] > best_size) {
                best_size = sz[v];
                best = v;
            }
        }
        son[u] = best;
    }

    // ---- 第二遍：分配 dfn，让整条重链的编号连成一段 ----
    // sz[u] 必须在这之前算好，因为子树区间 [dfn[u], dfn[u]+sz[u]-1] 依赖它。
    int timer = 0;
    int tp = 0;
    stk[tp++] = root;
    top[root] = root;
    while (tp > 0) {
        int u = stk[--tp];
        dfn[u] = ++timer;
        rev[timer] = u;
        base[timer] = a[u];
        // 轻儿子先入栈、重儿子后入栈，栈是后进先出，所以重儿子先被访问。
        // 每个轻儿子自己开一条新链，所以 top[v] = v。
        for (int v : g[u]) {
            if (v == fa[u] || v == son[u]) continue;
            top[v] = v;
            stk[tp++] = v;
        }
        if (son[u]) {
            top[son[u]] = top[u];  // 重儿子继承父节点的链头
            stk[tp++] = son[u];
        }
    }

    seg_build(1, 1, n);
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
        answer += range_sum(dfn[top[u]], dfn[u], 1, 1, n);
        answer %= mod;
        u = fa[top[u]];
    }
    if (dep[u] > dep[v]) swap(u, v);
    answer += range_sum(dfn[u], dfn[v], 1, 1, n);
    return answer % mod;
}

// 子树操作不需要跳链：以 u 为根的子树在 dfn 上正好是连续区间
// [dfn[u], dfn[u] + sz[u] - 1]，一次区间操作即可。
void subtree_add(int u, ll delta) {
    range_add(dfn[u], dfn[u] + sz[u] - 1, delta, 1, 1, n);
}

ll subtree_sum(int u) {
    return range_sum(dfn[u], dfn[u] + sz[u] - 1, 1, 1, n);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int count, m, root, modulus;
    cin >> count >> m >> root >> modulus;

    init(count, modulus);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] = norm(a[i]);  // 点权先取模，后面所有加法都在 [0, mod) 内滚动
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }

    build(root);

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
