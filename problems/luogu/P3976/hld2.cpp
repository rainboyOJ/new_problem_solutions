/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-29 17:40
 * update_at: 2026-10-29 17:40
 */
// hld2.cpp：解法二，树链剖分 + 线段树（四元摘要），按 rbook hld 模板的全局数组写法组织。
// 与 main.cpp 用同一个摘要和同一套合并式，差别只在「树剖查询的方向怎么攒」：
//   main.cpp：a 侧每段拼在累积器左边，全部走完后再统一 flip 一次；
//   本文件  ：每段先 flip 成真实旅行方向（x → 链头），再追加到累积器右边。
// 两种写法等价，本文件的好处是累积器每一步都已经是"从 a 出发、按旅行顺序"的摘要，
// 中途断点打印出来就能直接和暴力解对照，方向写错时更容易定位。
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int maxn = 50000 + 5;
const ll BIG = (ll)1e18; // 空段的最值用 ±BIG，保证不参与任何取最值

int n, q;

/*------------------------ sgt 代码 开始 ------------------------*/
// 线段树维护数组 base[1..n]，每个节点存一段价格序列的四元摘要：
//   mn / mx：段内最低 / 最高价
//   fwd（forward）  ：按 dfn 增序（先左后右）走过这段的最大利润
//   bwd（backward） ：按 dfn 减序（先右后左）走过这段的最大利润
ll base[maxn];
ll mn[maxn << 2];
ll mx[maxn << 2];
ll fwd[maxn << 2];
ll bwd[maxn << 2];
ll lz[maxn << 2]; // 区间加懒标记

int ls(int p) { return p << 1; }     // p 的左儿子 2p
int rs(int p) { return p << 1 | 1; } // p 的右儿子 2p+1

// 一段摘要
struct Info {
    ll mn, mx, fwd, bwd;
};

Info make_info(ll a, ll b, ll c, ll d) { return Info{a, b, c, d}; }

// 空段：不含任何城市
Info empty_info() { return Info{BIG, -BIG, 0, 0}; }

// 按「先走完 a、再走完 b」的顺序合并
Info join_info(Info a, Info b) {
    Info c;
    c.mn = min(a.mn, b.mn);
    c.mx = max(a.mx, b.mx);
    c.fwd = max(max(a.fwd, b.fwd), b.mx - a.mn); // 要么全在一边，要么左买右卖
    c.bwd = max(max(a.bwd, b.bwd), a.mx - b.mn); // 要么全在一边，要么右买左卖
    return c;
}

// 把一段的旅行方向倒过来：最值不变，两个方向的利润互换
Info flip_info(Info a) { return Info{a.mn, a.mx, a.bwd, a.fwd}; }

Info seg_info(int p) { return Info{mn[p], mx[p], fwd[p], bwd[p]}; }

// 整段加 value：最值一起平移，两个方向的利润是差值，保持不变
void apply_add(int p, ll value) {
    mn[p] += value;
    mx[p] += value;
    lz[p] += value;
}

void push_up(int p) {
    Info c = join_info(seg_info(ls(p)), seg_info(rs(p)));
    mn[p] = c.mn;
    mx[p] = c.mx;
    fwd[p] = c.fwd;
    bwd[p] = c.bwd;
}

void push_down(int p) {
    if (lz[p] == 0) return;
    apply_add(ls(p), lz[p]);
    apply_add(rs(p), lz[p]);
    lz[p] = 0;
}

void seg_build(int p, int l, int r) {
    lz[p] = 0;
    if (l == r) {
        mn[p] = mx[p] = base[l];
        fwd[p] = bwd[p] = 0; // 单个城市无法买卖
        return;
    }
    int mid = (l + r) >> 1;
    seg_build(ls(p), l, mid);
    seg_build(rs(p), mid + 1, r);
    push_up(p);
}

// 区间加
void range_add(int ql, int qr, ll value, int p, int l, int r) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) {
        apply_add(p, value);
        return;
    }
    push_down(p);
    int mid = (l + r) >> 1;
    range_add(ql, qr, value, ls(p), l, mid);
    range_add(ql, qr, value, rs(p), mid + 1, r);
    push_up(p);
}

// 区间摘要查询：返回的摘要按 dfn 增序（l → r）
Info range_query(int ql, int qr, int p, int l, int r) {
    if (qr < l || r < ql) return empty_info();
    if (ql <= l && r <= qr) return seg_info(p);
    push_down(p);
    int mid = (l + r) >> 1;
    return join_info(range_query(ql, qr, ls(p), l, mid),
                     range_query(ql, qr, rs(p), mid + 1, r));
}
/*------------------------ sgt 代码 结束 ------------------------*/

/*------------------------ hld 代码 开始 ------------------------*/
// 树链剖分：g 存树，6 个核心数组维护树上信息。
vector<int> g[maxn];
ll price[maxn]; // price[u]：城市 u 的当前价格（只用于建树时搬进 base）

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
    dep[u] = dep[father] + 1;
    sz[u] = 1;
    son[u] = 0;
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
    base[timer] = price[u];
    if (son[u]) dfs2(son[u], head);
    for (int v : g[u]) {
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v, v);
    }
}

void build(int root) {
    dfs1(root, 0);
    timer = 0;
    dfs2(root, root);
    seg_build(1, 1, n);
}

// a → b 整个路径的摘要，按真实旅行顺序（a 先、b 后）。
// a 侧向上走：区间 [dfn[top], dfn[x]] 的 dfn 增序是 top → x，与旅行方向相反，先 flip 再追加到右边；
// b 侧向下走：区间 [dfn[top], dfn[y]] 的 dfn 增序就是 top → y，正是旅行方向，直接前插到左边。
Info path_info(int a, int b) {
    Info left = empty_info();  // 已走过的 a 侧部分，始终是"从 a 出发"的顺序
    Info right = empty_info(); // 已收集的 b 侧部分，始终是"朝 b 去"的顺序
    int x = a, y = b;
    while (top[x] != top[y]) {
        if (dep[top[x]] >= dep[top[y]]) {
            left = join_info(left, flip_info(range_query(dfn[top[x]], dfn[x], 1, 1, n)));
            x = fa[top[x]];
        } else {
            right = join_info(range_query(dfn[top[y]], dfn[y], 1, 1, n), right);
            y = fa[top[y]];
        }
    }
    // 两点落在同一条重链上：x、y 中较深的那个先被走过
    if (dep[x] >= dep[y]) {
        left = join_info(left, flip_info(range_query(dfn[y], dfn[x], 1, 1, n)));
    } else {
        right = join_info(range_query(dfn[x], dfn[y], 1, 1, n), right);
    }
    return join_info(left, right);
}

// 路径上所有城市的价格同时加 value
void path_add(int a, int b, ll value) {
    int x = a, y = b;
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        range_add(dfn[top[x]], dfn[x], value, 1, 1, n);
        x = fa[top[x]];
    }
    if (dep[x] > dep[y]) swap(x, y);
    range_add(dfn[x], dfn[y], value, 1, 1, n);
}
/*------------------------ hld 代码 结束 ------------------------*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int u = 1; u <= n; ++u) g[u].clear();
    for (int i = 1; i <= n; i++) cin >> price[i];
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }

    build(1); // 根固定为 1

    cin >> q;
    while (q--) {
        int a, b;
        ll v;
        cin >> a >> b >> v;
        // 先按旅行方向问最大利润（亏本输出 0），再给路径整体加价
        Info res = path_info(a, b);
        cout << max(0LL, res.fwd) << '\n';
        path_add(a, b, v);
    }

    return 0;
}
