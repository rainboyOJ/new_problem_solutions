/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-21 03:09
 * update_at: 2026-10-29 12:52
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ===================== 重链剖分 + 线段树（区间和 + 区间最大值） =====================
// 骨架取自 rbook 模板 hld：定长全局数组 + 普通函数，没有 struct/class。
// 使用顺序：init(n) -> add_edge 加边 -> 读点权到 a[] -> build(1) -> 操作。
// 与模板的差别只在三处：本题不取模、根固定为 1、线段树是“单点改 + 和 + 最大值”。

const int maxn = 30000 + 5;        // 本题 n <= 30000。模板要求 n <= maxn，不能越界
const ll NEG_INF = -(1LL << 60);   // 查询最大值的初值，点权可能为负，不能用 0

int n;  // 节点个数

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
ll seg_sum[maxn << 2];  // seg_sum[u]：线段树节点 u 覆盖区间的点权和
ll seg_max[maxn << 2];  // seg_max[u]：线段树节点 u 覆盖区间的点权最大值

// 只清邻接表：旧边必须清掉，否则上一组的边会残留。
// 其余数组不必清零 —— build() 会逐点重写 fa/dep/sz/son/top/dfn/rev/base，
// 线段树的 seg_sum/seg_max 由 seg_build() 整体重写，旧值影响不到本组结果。
void init(int count) {
    n = count;
    for (int u = 1; u <= n; ++u) g[u].clear();
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
void seg_build(int u, int l, int r) {
    if (l == r) {
        seg_sum[u] = base[l];
        seg_max[u] = base[l];
        return;
    }
    int mid = (l + r) >> 1;
    seg_build(u << 1, l, mid);
    seg_build(u << 1 | 1, mid + 1, r);
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

// 路径 (u, v) 上所有点的和。
// 不在同一条重链时，处理“链头更深”那一侧的整段 [dfn[top[u]], dfn[u]]，
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

    build(1);  // 根固定为 1，题面没有给根

    int q;
    cin >> q;
    while (q--) {
        string op;
        int u, v;
        cin >> op >> u >> v;

        // 三种指令首字母不同，用 op[1] 区分，省去整串比较。
        if (op[1] == 'H') {
            a[u] = v;
            point_update(dfn[u], v, 1, 1, n);  // 单点修改走 dfn 位置
        } else if (op[1] == 'M') {
            cout << path_max(u, v) << '\n';
        } else {
            cout << path_sum(u, v) << '\n';
        }
    }

    return 0;
}
