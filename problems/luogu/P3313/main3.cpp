/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-30 07:51
 * update_at: 2026-10-30 07:51
 */
// main3.cpp：解法三 —— 只开一棵 dfn 线段树，每个节点挂一个 map：宗教 -> (区间内该宗教的评级和, 最大值)。
// 不用树链剖分以外的任何技巧，路径查询照旧拆段，只是「按宗教过滤」交给每个节点上的 map。
// 写法最短，但每个节点一次 map 查找都要 O(log C)，常数和内存都比前两个解法大。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXC = 100005;

int n, q;
int w[MAXN];    // w[i]：城市 i 的评级
int col[MAXN];  // col[i]：城市 i 的宗教

vector<int> g[MAXN]; // 树的邻接表

// ---- 树链剖分 ----
int parent_[MAXN]; // parent_[u]：u 的父亲
int depth[MAXN];   // depth[u]：u 的深度（根为 1）
int sz[MAXN];      // sz[u]：u 的子树大小
int heavy[MAXN];   // heavy[u]：u 的重儿子
int top[MAXN];     // top[u]：u 所在重链的链头
int dfn[MAXN];     // dfn[u]：u 剖分后的编号
int timer;         // dfn 计数器

// 一个节点里，某个宗教的摘要
struct Info {
    int sum; // 该宗教在这些位置上的评级和
    int mx;  // 该宗教在这些位置上的评级最大值
};

map<int, Info> node_of_color[MAXN << 2]; // node_of_color[p]：节点 p 的区间里「宗教 -> 摘要」

void dfs1(int u, int f) {
    parent_[u] = f;
    depth[u] = depth[f] + 1;
    sz[u] = 1;
    heavy[u] = 0;
    for (auto v : g[u]) {
        if (v == f) {
            continue;
        }
        dfs1(v, u);
        sz[u] += sz[v];
        if (heavy[u] == 0 || sz[v] > sz[heavy[u]]) {
            heavy[u] = v;
        }
    }
}

void dfs2(int u, int chain_top) {
    top[u] = chain_top;
    dfn[u] = ++timer;
    if (heavy[u] != 0) {
        dfs2(heavy[u], chain_top);
    }
    for (auto v : g[u]) {
        if (v == parent_[u] || v == heavy[u]) {
            continue;
        }
        dfs2(v, v);
    }
}

// 取节点 p 在宗教 c 上的和 / 最大值，没有该宗教就是 0。
int get_sum(int p, int c) {
    auto it = node_of_color[p].find(c);
    return it == node_of_color[p].end() ? 0 : it->second.sum;
}

int get_max(int p, int c) {
    auto it = node_of_color[p].find(c);
    return it == node_of_color[p].end() ? 0 : it->second.mx;
}

// 把位置 pos 上的宗教 c 的评级写成 val；val 为 0 表示这个位置不再属于宗教 c。
// 递归回来后只需要重算宗教 c 这一项，别的宗教没被改过。
void point_set(int p, int l, int r, int pos, int c, int val) {
    if (l == r) {
        if (val == 0) {
            node_of_color[p].erase(c);
        } else {
            Info info;
            info.sum = val;
            info.mx = val;
            node_of_color[p][c] = info;
        }
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) {
        point_set(p << 1, l, mid, pos, c, val);
    } else {
        point_set(p << 1 | 1, mid + 1, r, pos, c, val);
    }
    int sum = get_sum(p << 1, c) + get_sum(p << 1 | 1, c);
    if (sum == 0) {
        node_of_color[p].erase(c); // 这个宗教在本节点的区间里已经空了
        return;
    }
    Info info;
    info.sum = sum;
    info.mx = max(get_max(p << 1, c), get_max(p << 1 | 1, c));
    node_of_color[p][c] = info;
}

// 在区间 [ql, qr] 里查宗教 c 的和与最大值。
void range_query(int p, int l, int r, int ql, int qr, int c, int &tsum, int &tmax) {
    if (ql <= l && r <= qr) {
        tsum += get_sum(p, c);
        tmax = max(tmax, get_max(p, c));
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        range_query(p << 1, l, mid, ql, qr, c, tsum, tmax);
    }
    if (qr > mid) {
        range_query(p << 1 | 1, mid + 1, r, ql, qr, c, tsum, tmax);
    }
}

// HLD 拆段后，每段都用宗教 rel 去查。
void path_query(int x, int y, int rel, int &tsum, int &tmax) {
    while (top[x] != top[y]) {
        if (depth[top[x]] < depth[top[y]]) {
            swap(x, y);
        }
        range_query(1, 1, n, dfn[top[x]], dfn[x], rel, tsum, tmax);
        x = parent_[top[x]];
    }
    if (depth[x] > depth[y]) {
        swap(x, y);
    }
    range_query(1, 1, n, dfn[x], dfn[y], rel, tsum, tmax);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> col[i];
    }
    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }

    dfs1(1, 0);
    dfs2(1, 1);

    for (int i = 1; i <= n; i++) {
        point_set(1, 1, n, dfn[i], col[i], w[i]);
    }

    while (q--) {
        string op;
        int x, y;
        cin >> op >> x >> y;
        if (op == "CC") {
            point_set(1, 1, n, dfn[x], col[x], 0);
            col[x] = y;
            point_set(1, 1, n, dfn[x], col[x], w[x]);
        } else if (op == "CW") {
            w[x] = y;
            point_set(1, 1, n, dfn[x], col[x], y);
        } else {
            int tsum = 0;
            int tmax = 0;
            path_query(x, y, col[x], tsum, tmax);
            if (op == "QS") {
                cout << tsum << '\n';
            } else {
                cout << tmax << '\n';
            }
        }
    }

    return 0;
}
