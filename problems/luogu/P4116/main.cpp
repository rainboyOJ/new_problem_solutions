/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:59
 * update_at: 2026-08-12 22:59
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int INF = 0x3f3f3f3f;

int n, q;
vector<int> g[MAXN]; // 邻接表存树

// ---------- 树链剖分相关数组（根为 1） ----------
int parent[MAXN];     // parent[u]：u 的父亲
int depth[MAXN];      // depth[u]：u 的深度
int sz[MAXN];         // sz[u]：u 的子树大小
int heavy_son[MAXN];  // heavy_son[u]：u 的重儿子（子树最大的儿子）
int top[MAXN];        // top[u]：u 所在重链的链头
int dfn[MAXN];        // dfn[u]：u 的 DFS 新编号
int node_at[MAXN];    // node_at[dfn]：新编号对应的原节点
int timer;            // DFS 编号计时器

// ---------- 线段树：维护区间内黑点的最小 dfn ----------
int tree[MAXN * 4];   // tree[p]：节点 p 区间内黑点 dfn 的最小值，没有黑点为 INF
bool black[MAXN];     // black[u]：节点 u 当前是否为黑点

// 点更新：把位置 pos 的值改成 value。
void seg_update(int p, int l, int r, int pos, int value) {
    if (l == r) {
        tree[p] = value;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        seg_update(p << 1, l, mid, pos, value);
    else
        seg_update(p << 1 | 1, mid + 1, r, pos, value);
    tree[p] = min(tree[p << 1], tree[p << 1 | 1]);
}

// 区间查询：返回区间 [ql, qr] 内黑点的最小 dfn，没有黑点返回 INF。
int seg_query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return tree[p];
    int mid = (l + r) >> 1;
    int res = INF;
    if (ql <= mid) res = min(res, seg_query(p << 1, l, mid, ql, qr));
    if (qr > mid) res = min(res, seg_query(p << 1 | 1, mid + 1, r, ql, qr));
    return res;
}

// 切换节点 u 的颜色，并更新线段树对应叶子。
void toggle(int u) {
    black[u] = !black[u];
    int value = black[u] ? dfn[u] : INF;
    seg_update(1, 1, n, dfn[u], value);
}

// 查询根 1 到 v 的路径上深度最小的黑点（即第一个黑点），没有则返回 -1。
int query_first_black(int v) {
    vector<pair<int, int>> segments; // 记录路径拆出的重链段，从 v 往根方向收集
    int u = v;
    while (top[u] != 1) {
        segments.push_back(make_pair(dfn[top[u]], dfn[u]));
        u = parent[top[u]];
    }
    segments.push_back(make_pair(dfn[1], dfn[u])); // 最后一段包含根 1

    // 从根侧往 v 方向逐段查询，第一段出现黑点的就是答案所在段。
    // 段内 dfn 最小即深度最小，所以第一个非 INF 的 dfn 就是最浅黑点。
    for (int i = (int)segments.size() - 1; i >= 0; i--) {
        int l = segments[i].first;
        int r = segments[i].second;
        int min_dfn = seg_query(1, 1, n, l, r);
        if (min_dfn != INF)
            return node_at[min_dfn];
    }
    return -1;
}

// 预处理：按 BFS 序求父亲、深度，逆序求子树大小和重儿子。
// 用迭代写法，避免 1e5 深链上递归 DFS 撑爆系统栈。
void preprocess(int root) {
    vector<int> order; // BFS 访问顺序，父节点总在子节点之前
    order.push_back(root);
    depth[root] = 1;
    for (int i = 0; i < (int)order.size(); i++) {
        int u = order[i];
        for (int j = 0; j < (int)g[u].size(); j++) {
            int v = g[u][j];
            if (v == parent[u]) continue; // 跳过父节点
            parent[v] = u;
            depth[v] = depth[u] + 1;
            order.push_back(v);
        }
    }
    // 子树大小：按 BFS 逆序向上累加，顺便找出每个点的重儿子。
    for (int i = (int)order.size() - 1; i >= 0; i--) {
        int u = order[i];
        sz[u] = 1;
        heavy_son[u] = 0;
        for (int j = 0; j < (int)g[u].size(); j++) {
            int v = g[u][j];
            if (v == parent[u]) continue;
            sz[u] += sz[v];
            if (heavy_son[u] == 0 || sz[v] > sz[heavy_son[u]])
                heavy_son[u] = v;
        }
    }
}

// 第二次 DFS：优先走重儿子分配连续 dfn，轻儿子开启新链。
// 用栈模拟递归，保证链头到链尾的 dfn 严格递增。
void decompose(int root) {
    vector<pair<int, int>> st; // (节点, 链头)，先处理根所在重链
    st.push_back(make_pair(root, root));
    while (!st.empty()) {
        pair<int, int> cur = st.back();
        st.pop_back();
        int u = cur.first;
        int chain_top = cur.second;
        while (u != 0) {
            top[u] = chain_top;
            timer++;
            dfn[u] = timer;
            node_at[timer] = u;
            for (int j = 0; j < (int)g[u].size(); j++) {
                int v = g[u][j];
                if (v != parent[u] && v != heavy_son[u])
                    st.push_back(make_pair(v, v)); // 轻儿子开启新链
            }
            u = heavy_son[u]; // 重儿子继续当前链
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    preprocess(1);
    decompose(1);

    fill(tree, tree + MAXN * 4, INF); // 初始全白，整棵树没有黑点

    while (q--) {
        int op, x;
        cin >> op >> x;
        if (op == 0)
            toggle(x);
        else
            cout << query_first_black(x) << '\n';
    }

    return 0;
}
