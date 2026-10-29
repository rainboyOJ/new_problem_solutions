/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 20:05
 * update_at: 2026-10-29 16:52
 */
#include <bits/stdc++.h>
using namespace std;

// 树链剖分（HLD）+ 线段树，节点与区间均为 1 下标。
// 线段树维护「区间内黑点的最小 dfn」，查询时从根侧往 v 侧逐段查重链段。
// 参考 rbook 模板 hld 的全局数组 + 普通函数写法，只保留本题需要的部分。

const int maxn = 100000 + 5;
const int INF = 0x3f3f3f3f;

int n, q;

/*------------------------ sgt 代码 开始 ------------------------*/
// 线段树：维护数组 base[1..n]，支持单点改、区间最小值。
// base[t] = 黑点 ? t : INF；内部节点存左右儿子的较小值。
int base[maxn];
int tree[maxn << 2];

int ls(int p) { return p << 1; }     // p 的左儿子 2p
int rs(int p) { return p << 1 | 1; } // p 的右儿子 2p+1

void push_up(int p) {
    tree[p] = min(tree[ls(p)], tree[rs(p)]);
}

void seg_build(int p, int l, int r) {
    if (l == r) {
        tree[p] = base[l];
        return;
    }
    int mid = (l + r) >> 1;
    seg_build(ls(p), l, mid);
    seg_build(rs(p), mid + 1, r);
    push_up(p);
}

// 单点改：把 dfn 位置 pos 的值改成 value。
void point_update(int pos, int value, int p, int l, int r) {
    if (l == r) {
        tree[p] = value;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) point_update(pos, value, ls(p), l, mid);
    else point_update(pos, value, rs(p), mid + 1, r);
    push_up(p);
}

// 区间最小值：不相交的分支返回 INF，不参与 min。
int range_min(int ql, int qr, int p, int l, int r) {
    if (qr < l || r < ql) return INF;     // 不相交
    if (ql <= l && r <= qr) return tree[p]; // 完全包含
    int mid = (l + r) >> 1;
    int answer = range_min(ql, qr, ls(p), l, mid);
    answer = min(answer, range_min(ql, qr, rs(p), mid + 1, r));
    return answer;
}
/*------------------------ sgt 代码 结束 ------------------------*/

/*------------------------ hld 代码 开始 ------------------------*/
// 树链剖分：g 存树，6 个核心数组维护树上信息。
vector<int> g[maxn];

int fa[maxn];  // fa[u]：父亲，根的 fa 为 0
int dep[maxn]; // dep[u]：深度，根为 1
int sz[maxn];  // sz[u]：子树大小（含自己）
int son[maxn]; // son[u]：重儿子，叶子为 0
int top[maxn]; // top[u]：所在重链的链头
int dfn[maxn]; // dfn[u]：线段树上的位置（DFS 新编号）
int node_at[maxn]; // node_at[t]：dfn 为 t 的原节点
int timer;

bool black[maxn]; // black[u]：节点 u 当前是否为黑点

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

// 第二遍 DFS：重儿子优先分配 dfn，保证重链连续且链内 dfn 随深度递增
void dfs2(int u, int head) {
    top[u] = head;
    dfn[u] = ++timer;
    node_at[timer] = u;
    if (son[u]) dfs2(son[u], head);
    for (int v : g[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

// 预处理入口：加完边之后调用一次。
void build(int root) {
    dfs1(root, 0);    // 填 fa / dep / sz / son
    timer = 0;        // 从 1 重新分配 dfn
    dfs2(root, root); // 填 top / dfn / node_at
    // 初始全白，所有叶子的值都是 INF
    for (int i = 1; i <= n; i++) base[i] = INF;
    seg_build(1, 1, n);
}

// 查询根 1 到 v 的路径上最浅的黑点编号，没有则返回 -1。
// 先把路径拆成若干重链段（从 v 向根收集），再按根侧到 v 侧的顺序逐段查最小值，
// 第一个出现的黑点就是答案（链内 dfn 与深度同序，区间最小值即最浅黑点）。
int query_first_black(int v) {
    vector<pair<int, int>> segments; // 每段是 [链头 dfn, 当前节点 dfn]
    int u = v;
    while (top[u] != 1) {
        segments.push_back(make_pair(dfn[top[u]], dfn[u]));
        u = fa[top[u]];
    }
    segments.push_back(make_pair(dfn[1], dfn[u])); // 最后一段一定包含根 1

    for (int i = (int)segments.size() - 1; i >= 0; i--) {
        int min_dfn = range_min(segments[i].first, segments[i].second, 1, 1, n);
        if (min_dfn != INF) return node_at[min_dfn];
    }
    return -1;
}
/*------------------------ hld 代码 结束 ------------------------*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) g[i].clear();

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }

    build(1); // 根固定为 1

    while (q--) {
        int op, x;
        cin >> op >> x;
        if (op == 0) {
            // 取反颜色：黑点存自己的 dfn，白点存 INF
            black[x] = !black[x];
            point_update(dfn[x], black[x] ? dfn[x] : INF, 1, 1, n);
        } else {
            cout << query_first_black(x) << '\n';
        }
    }

    return 0;
}
