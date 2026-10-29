/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:29
 * update_at: 2026-10-29 09:40
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ===================== 重链剖分 + 懒标记线段树 =====================
// 骨架取自 rbook 模板 hld：全部是全局数组加普通函数，没有 struct/class。
// 使用顺序：init -> 读点权到 a[] -> add_edge 加边 -> build(root) -> 四种操作。
// 节点编号、dfn 编号、线段树下标全部 1 起；只在 mod 处取模，其余按 ll 存。

int n;          // 节点个数
int mod;        // 题目给定的取模数 P，所有输出都对它取模
vector<vector<int>> g;      // g[u]：u 的邻接表（无向树，两边都存）
vector<int> fa;             // fa[u]：父亲，根的 fa 为 0
vector<int> dep;            // dep[u]：深度，根为 1
vector<int> sz;             // sz[u]：子树节点数（含 u 自己）
vector<int> son;            // son[u]：重儿子（子树最大的儿子），叶子为 0
vector<int> top;            // top[u]：u 所在重链的链头
vector<int> dfn;            // dfn[u]：u 在线段树上的位置（DFS 新编号）
vector<int> rev;            // rev[t]：dfn 位置 t 对应的原节点
vector<ll> a;               // a[u]：原树上的点权
vector<ll> base;            // base[t]：按 dfn 重排后的点权，线段树直接建在它上面
vector<ll> tr;              // tr[u]：线段树节点 u 覆盖区间的和（已取模）
vector<ll> lazy;            // lazy[u]：节点 u 上欠着、还没下发的"整段加"的值

// 把任意整数规整到 [0, mod) 内，保证取模后不会出现负数。
ll norm(ll x) { return (x % mod + mod) % mod; }

void init(int count, int modulus) {
    n = count;
    mod = modulus;
    g.assign(n + 1, {});
    fa.assign(n + 1, 0);
    dep.assign(n + 1, 0);
    sz.assign(n + 1, 0);
    son.assign(n + 1, 0);
    top.assign(n + 1, 0);
    dfn.assign(n + 1, 0);
    rev.assign(n + 1, 0);
    a.assign(n + 1, 0);
    base.assign(n + 1, 0);
    // 线段树按 4n 开空间：二叉树用 4n 个下标一定装得下。
    tr.assign(4 * n + 5, 0);
    lazy.assign(4 * n + 5, 0);
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
void seg_build(int u, int l, int r, const vector<ll> &base) {
    if (l == r) {
        tr[u] = norm(base[l]);
        return;
    }
    int mid = (l + r) >> 1;
    seg_build(u << 1, l, mid, base);
    seg_build(u << 1 | 1, mid + 1, r, base);
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

// ---------------- 树链剖分：两遍 DFS + 跳链 ----------------

// 第一遍：定父亲和深度（正序），再从下往上汇总子树大小、选出重儿子（逆序）。
// 两趟都用"先把 BFS 顺序记下来"的写法，避免链形树上递归深度达到 O(n)。
void build(int root) {
    // 正序：order 是父亲一定排在儿子前面的一个遍历顺序。
    vector<int> order{root};
    dep[root] = 1;
    for (int i = 0; i < n; ++i) {
        int u = order[i];
        for (int v : g[u]) {
            if (v == fa[u]) continue;    // 只认父亲，其余都是儿子
            fa[v] = u;
            dep[v] = dep[u] + 1;
            order.push_back(v);
        }
    }
    // 逆序：儿子的信息都算完了，再汇总到父亲身上。
    for (int i = n - 1; i >= 0; --i) {
        int u = order[i];
        sz[u] = 1;
        for (int v : g[u]) {
            if (v == fa[u]) continue;
            sz[u] += sz[v];
            // 子树最大的儿子就是重儿子；sz[0] == 0 顺带处理了"还没有重儿子"。
            if (sz[v] > sz[son[u]]) son[u] = v;
        }
    }

    // 第二遍：分配 dfn。始终优先走重儿子，让整条重链的编号连成一段。
    // sz[u] 一定要在分配 dfn 之前算好，因为子树区间 [dfn[u], dfn[u]+sz[u]-1]
    // 依赖它。
    int timer = 0;
    vector<int> st{root};
    top[root] = root;
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        dfn[u] = ++timer;
        rev[timer] = u;
        base[timer] = a[u];
        // 轻儿子先入栈、重儿子后入栈，栈是后进先出，所以重儿子先被访问。
        // 每个轻儿子自己开一条新链，所以 top[v] = v。
        for (int v : g[u]) {
            if (v == fa[u] || v == son[u]) continue;
            top[v] = v;
            st.push_back(v);
        }
        if (son[u]) {
            top[son[u]] = top[u];    // 重儿子继承父节点的链头
            st.push_back(son[u]);
        }
    }
    seg_build(1, 1, n, base);
}

// 路径 (u, v) 上所有点加 delta。
// 不在同一条重链时，先处理"链头更深"那一侧的整段 [dfn[top[u]], dfn[u]]，
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
        a[i] = norm(a[i]);    // 点权先取模，后面所有加法都在 [0, mod) 内滚动
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
