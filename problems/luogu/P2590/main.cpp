/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-21 03:09
 * update_at: 2026-10-29 16:05
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ===================== 重链剖分 + 线段树（区间和 + 区间最大值） =====================
// 骨架取自 rbook 模板 hld：全部是全局数组加普通函数，没有 struct/class。
// 模板把代码分成两段：sgt 段只管数组 base[1..n] 上的统计，hld 段负责把树上路径
// 翻译成 base 上的连续区间。本题按题意改了三处：
//   1. 不取模（去掉 mod 与 norm）；
//   2. 只有单点修改，所以线段树不需要懒标记，只要 push_up；
//   3. 同时维护区间和与区间最大值。
// 使用顺序：直接读 n -> add_edge 加边 -> 读点权到 a[] -> build(1) -> 操作。
// 节点编号、dfn 编号、线段树下标全部 1 起。

const int maxn = 30000 + 5;      // 本题 n <= 30000。模板要求 n <= maxn，不能越界
const ll NEG_INF = -(1LL << 60); // 查询最大值的初值，点权可能为负，不能用 0

int n; // 节点数

/*------------------------ sgt 代码 开始 ------------------------*/
// 线段树：维护数组 base[1..n]，支持单点改、区间和、区间最大值。
ll base[maxn];       // base[t]：按 dfn 重排后的点权，线段树就建在它上面
ll tr[maxn << 2];    // tr[p]：节点 p 覆盖区间的和
ll mx[maxn << 2];    // mx[p]：节点 p 覆盖区间的最大值

int ls(int p) { return p << 1; }     // p 的左儿子 2p
int rs(int p) { return p << 1 | 1; } // p 的右儿子 2p+1

// 用左右儿子的信息重算 p：和相加，最大值取大。
void push_up(int p) {
    tr[p] = tr[ls(p)] + tr[rs(p)];
    mx[p] = max(mx[ls(p)], mx[rs(p)]);
}

// 用 base[1..n] 建树。
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

// 单点修改：把 dfn 位置 pos 的点权改成 value。整条祖先路径重算一遍。
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

// 区间和：与模板的 range_sum 同一副四分式骨架。
ll range_sum(int ql, int qr, int p, int l, int r) {
    if (qr < l || r < ql) return 0;       // 不相交
    if (ql <= l && r <= qr) return tr[p]; // 完全包含
    int mid = (l + r) >> 1;
    ll answer = range_sum(ql, qr, ls(p), l, mid);
    answer += range_sum(ql, qr, rs(p), mid + 1, r);
    return answer;
}

// 区间最大值：不相交的分支返回 NEG_INF，不参与 max。
ll range_max(int ql, int qr, int p, int l, int r) {
    if (qr < l || r < ql) return NEG_INF;  // 不相交
    if (ql <= l && r <= qr) return mx[p];  // 完全包含
    int mid = (l + r) >> 1;
    ll answer = range_max(ql, qr, ls(p), l, mid);
    answer = max(answer, range_max(ql, qr, rs(p), mid + 1, r));
    return answer;
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

// 预处理入口：加完边、读完点权之后调用一次。其余数组在 dfs1 / dfs2 / seg_build 里
// 逐点覆写，所以不需要事先清零。sz[u] 必须在 dfs2 之前算好，因为子树区间
// [dfn[u], dfn[u] + sz[u] - 1] 依赖它。
void build(int root) {
    dfs1(root, 0);      // 填 fa / dep / sz / son
    timer = 0;          // 从 1 重新分配 dfn
    dfs2(root, root);   // 填 top / dfn / base
    seg_build(1, 1, n); // 交给 sgt 段
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
/*------------------------ hld 代码 结束 ------------------------*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

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

    build(1); // 根固定为 1，题面没有给根

    int q;
    cin >> q;
    while (q--) {
        string op;
        int u, v;
        cin >> op >> u >> v;

        // 三种指令首字母不同，用 op[1] 区分，省去整串比较。
        if (op[1] == 'H') {
            a[u] = v;
            point_update(dfn[u], v, 1, 1, n); // 单点修改走 dfn 位置
        } else if (op[1] == 'M') {
            cout << path_max(u, v) << '\n';
        } else {
            cout << path_sum(u, v) << '\n';
        }
    }

    return 0;
}
