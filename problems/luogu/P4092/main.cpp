/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:59
 * update_at: 2026-08-12 22:59
 */
// main.cpp：重链剖分 + 线段树维护区间最大 dfn，查询节点到根路径上最近的已标记祖先。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, q;
vector<int> children[MAXN]; // children[u] 记录 u 的儿子列表（输入是 u -> v 的有向边）
int parent[MAXN];           // parent[u] 记录 u 的父亲
int depth[MAXN];            // depth[u] 记录 u 的深度
int subtree_size[MAXN];     // subtree_size[u] 记录 u 的子树大小
int heavy_son[MAXN];        // heavy_son[u] 记录 u 的重儿子（子树最大的儿子）
int top[MAXN];              // top[u] 记录 u 所在重链的链头
int dfn[MAXN];              // dfn[u] 记录 u 剖分后的新编号
int node_at[MAXN];          // node_at[dfn] 是编号 dfn 对应的原节点

// ---------- 线段树：维护区间内最大的已标记 dfn ----------
int seg_tree[MAXN * 4]; // seg_tree[p] 保存节点 p 区间内最大的已标记 dfn，0 表示该区间没有标记

// 给位置 pos 打标记（标记幂等：重复写同一个 dfn 结果不变）。
void point_mark(int p, int l, int r, int pos) {
    if (l == r) {
        seg_tree[p] = pos;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid)
        point_mark(p << 1, l, mid, pos);
    else
        point_mark(p << 1 | 1, mid + 1, r, pos);
    seg_tree[p] = max(seg_tree[p << 1], seg_tree[p << 1 | 1]);
}

// 查询区间 [ql, qr] 内最大的已标记 dfn，0 表示区间内没有标记。
int range_max(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr)
        return seg_tree[p];
    int mid = (l + r) >> 1;
    int res = 0;
    if (ql <= mid)
        res = max(res, range_max(p << 1, l, mid, ql, qr));
    if (qr > mid)
        res = max(res, range_max(p << 1 | 1, mid + 1, r, ql, qr));
    return res;
}

// 询问节点 u 到根路径上最近的已标记祖先（u 本身也算祖先）。
int query_marked_ancestor(int u) {
    while (top[u] != 1) {
        // 先看当前链 [top[u], u] 上有没有标记，有则取 dfn 最大的（就是最近的）。
        int got = range_max(1, 1, n, dfn[top[u]], dfn[u]);
        if (got != 0)
            return node_at[got];
        // 当前链没有标记，跨过一条轻边，去上一段重链继续找。
        u = parent[top[u]];
    }
    // u 与根 1 同链：区间 [dfn[1], dfn[u]] 上一定有标记（根 1 永远有标记）。
    return node_at[range_max(1, 1, n, dfn[1], dfn[u])];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    // 读入 n-1 条有向边 u -> v，表示 u 是 v 的父亲。
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        children[u].push_back(v);
    }

    // 从根 1 出发 BFS：确定 parent、depth，并得到从根到叶的访问顺序 order。
    int order[MAXN];
    int order_len = 0;
    int bfs_queue[MAXN];
    int head = 0, tail = 0;
    bfs_queue[tail++] = 1;
    while (head < tail) {
        int u = bfs_queue[head++];
        order[order_len++] = u;
        for (int i = 0; i < (int)children[u].size(); i++) {
            int v = children[u][i];
            parent[v] = u;
            depth[v] = depth[u] + 1;
            bfs_queue[tail++] = v;
        }
    }

    // 逆序遍历 order：累计子树大小，选出每个点的重儿子。
    for (int i = 1; i <= n; i++)
        subtree_size[i] = 1;
    for (int i = n - 1; i >= 1; i--) {
        int u = order[i];
        subtree_size[parent[u]] += subtree_size[u];
        if (subtree_size[u] > subtree_size[heavy_son[parent[u]]])
            heavy_son[parent[u]] = u;
    }

    // 重链剖分编号（栈模拟 DFS）：重儿子优先连续编号，轻儿子开启新链。
    int stk_u[MAXN], stk_t[MAXN]; // 栈：待处理的节点和它的链头
    int stk_len = 0;
    int timer = 0;
    stk_u[++stk_len] = 1;
    stk_t[stk_len] = 1;
    while (stk_len) {
        int u = stk_u[stk_len], t = stk_t[stk_len];
        stk_len--;
        // 沿重儿子一路走到链尾，整条重链的 dfn 连续。
        while (u) {
            top[u] = t;
            dfn[u] = ++timer;
            node_at[timer] = u;
            // 轻儿子是新链的链头，先压栈，之后处理。
            for (int i = 0; i < (int)children[u].size(); i++) {
                int v = children[u][i];
                if (v != heavy_son[u]) {
                    stk_u[++stk_len] = v;
                    stk_t[stk_len] = v;
                }
            }
            u = heavy_son[u];
        }
    }

    // 初始只有根 1 有标记。
    point_mark(1, 1, n, dfn[1]);

    while (q--) {
        char opt;
        int u;
        cin >> opt >> u;
        if (opt == 'C')
            point_mark(1, 1, n, dfn[u]); // 标记：点更新
        else
            cout << query_marked_ancestor(u) << '\n'; // 询问：沿链查询
    }

    return 0;
}
