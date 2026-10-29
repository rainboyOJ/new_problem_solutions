/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-21 03:09
 * update_at: 2026-10-29 09:40
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ===================== 重链剖分 + 线段树（区间和 + 区间最大值） =====================
// 骨架取自 rbook 模板 hld：全部是全局数组加普通函数，没有 struct/class。
// 使用顺序：init -> add_edge 加边 -> 读点权到 a[] -> build(1) -> 操作。
// 与模板的区别只在两点：根固定为 1（本题不给根），线段树改成"单点改 + 和 + 最大值"。
// 节点编号、dfn 编号、线段树下标全部 1 起。

const ll NEG_INF = -(1LL << 60); // 查询最大值的初值，点权可能为负，不能用 0

int n;                       // 节点个数
vector<vector<int>> g;       // g[u]：u 的邻接表（无向树，两边都存）
vector<int> fa;              // fa[u]：父亲，根的 fa 为 0
vector<int> dep;             // dep[u]：深度，根为 1
vector<int> sz;              // sz[u]：子树节点数（含 u 自己）
vector<int> son;             // son[u]：重儿子（子树最大的儿子），叶子为 0
vector<int> top;             // top[u]：u 所在重链的链头
vector<int> dfn;             // dfn[u]：u 在线段树上的位置（DFS 新编号）
vector<int> rev;             // rev[t]：dfn 位置 t 对应的原节点
vector<ll> a;                // a[u]：原树上的点权
vector<ll> base;             // base[t]：按 dfn 重排后的点权，线段树直接建在它上面
vector<ll> seg_sum;          // seg_sum[u]：线段树节点 u 覆盖区间的点权和
vector<ll> seg_max;          // seg_max[u]：线段树节点 u 覆盖区间的点权最大值

void init(int count) {
    n = count;
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
    seg_sum.assign(4 * n + 5, 0);
    seg_max.assign(4 * n + 5, NEG_INF);
}

void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

// ---------------- 线段树：单点修改、区间和、区间最大值 ----------------
// 本题两种查询都先落到 dfn 上的连续区间，再交给这两个原语。

// 用左右儿子的信息重算 u：和相加，最大值取大。
void push_up(int u) {
    seg_sum[u] = seg_sum[u << 1] + seg_sum[u << 1 | 1];
    seg_max[u] = max(seg_max[u << 1], seg_max[u << 1 | 1]);
}

// 用 base[1..n]（按 dfn 排列好的点权）建树。
void seg_build(int u, int l, int r, const vector<ll> &base) {
    if (l == r) {
        seg_sum[u] = base[l];
        seg_max[u] = base[l];
        return;
    }
    int mid = (l + r) >> 1;
    seg_build(u << 1, l, mid, base);
    seg_build(u << 1 | 1, mid + 1, r, base);
    push_up(u);
}

// 把 dfn 位置 pos 的点权改成 new_value。整条路径上重算一遍即可。
void point_update(int pos, ll new_value, int u, int l, int r) {
    if (l == r) {
        seg_sum[u] = new_value;
        seg_max[u] = new_value;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) point_update(pos, new_value, u << 1, l, mid);
    else point_update(pos, new_value, u << 1 | 1, mid + 1, r);
    push_up(u);
}

// 询问区间 [ql, qr] 的和。
ll range_sum(int ql, int qr, int u, int l, int r) {
    if (ql <= l && r <= qr) return seg_sum[u];
    int mid = (l + r) >> 1;
    ll answer = 0;
    if (ql <= mid) answer += range_sum(ql, qr, u << 1, l, mid);
    if (qr > mid) answer += range_sum(ql, qr, u << 1 | 1, mid + 1, r);
    return answer;
}

// 询问区间 [ql, qr] 的最大值。没有交集的分支返回 NEG_INF，不参与 max。
ll range_max(int ql, int qr, int u, int l, int r) {
    if (ql <= l && r <= qr) return seg_max[u];
    int mid = (l + r) >> 1;
    ll answer = NEG_INF;
    if (ql <= mid) answer = max(answer, range_max(ql, qr, u << 1, l, mid));
    if (qr > mid) answer = max(answer, range_max(ql, qr, u << 1 | 1, mid + 1, r));
    return answer;
}

// ---------------- 树链剖分：两遍 DFS + 跳链 ----------------

// 第一遍：定父亲和深度（正序），再从下往上汇总子树大小、选出重儿子（逆序）。
// 两趟都用"先把遍历顺序记下来"的写法，避免链形树上递归深度达到 O(n)。
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

// 路径 (u, v) 上所有点的和。
// 不在同一条重链时，先处理"链头更深"那一侧的整段 [dfn[top[u]], dfn[u]]，
// 然后 u 跳到链头的父亲，即跨过一条轻边。每条轻边都让子树大小至少翻倍，
// 所以最多跳 O(log n) 次。两侧链头相同时，剩下的就是同一条链上的一段区间。
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    init(n);

    // 本题先给边、再给点权：add_edge 只用邻接表，a[] 晚点读也不影响，
    // 因为 build() 里才把 a[] 写进 base[]。
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    build(1);    // 根固定为 1，题面没有给根

    int q;
    cin >> q;
    while (q--) {
        string op;
        int u, v;
        cin >> op >> u >> v;

        // 三种指令首字母不同，用 op[1] 区分，省去整串比较。
        if (op[1] == 'H') {
            a[u] = v;
            point_update(dfn[u], v, 1, 1, n);   // 单点修改走 dfn 位置
        } else if (op[1] == 'M') {
            cout << path_max(u, v) << '\n';
        } else {
            cout << path_sum(u, v) << '\n';
        }
    }

    return 0;
}
