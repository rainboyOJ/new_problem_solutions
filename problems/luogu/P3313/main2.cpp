/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-30 07:51
 * update_at: 2026-10-30 07:51
 */
// main2.cpp：解法二 —— 离线读入所有操作，把「每个宗教历史上出现过的 dfn」离散化，
// 于是每种宗教都能用一棵普通（静态数组）线段树，节点总数 O(n + q)，完全不用动态开点。
// 代价是要先把全部操作读进来，并多做一次 dfn -> 该宗教内部下标的映射。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXC = 100005; // 宗教编号上限

int n, q;
int w[MAXN];    // w[i]：城市 i 的评级
int col[MAXN];  // col[i]：城市 i 的宗教

vector<int> g[MAXN]; // 树的邻接表

// ---- 树链剖分 ----
int parent_[MAXN];  // parent_[u]：u 的父亲
int depth[MAXN];    // depth[u]：u 的深度（根为 1）
int sz[MAXN];       // sz[u]：u 的子树大小
int heavy[MAXN];    // heavy[u]：u 的重儿子，0 表示没有
int top[MAXN];      // top[u]：u 所在重链的链头
int dfn[MAXN];      // dfn[u]：u 剖分后的编号
int timer;          // dfn 计数器

// 一次操作：type 是 CC / CW / QS / QM，x 是城市，y 是参数（宗教 / 评级 / 终点）
struct Op {
    char type[3];
    int x;
    int y;
};
Op ops[MAXN]; // ops[i]：第 i 条操作
int cur[MAXN]; // cur[i]：离线模拟时城市 i 当前的宗教

// 每种宗教的离散化坐标：pos[c] 是宗教 c 历史上的所有 dfn，升序去重
vector<int> pos[MAXN];
int base[MAXN];     // base[c]：宗教 c 的线段树在池里的起点
int kcnt[MAXN];     // kcnt[c]：宗教 c 的坐标个数，线段树下标是 1..kcnt[c]
vector<int> seg_sum; // 节点池：区间和
vector<int> seg_max; // 节点池：区间最大值

// 第一次 dfs：求父亲、深度、子树大小、重儿子。
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

// 第二次 dfs：先走重儿子，让每条重链的 dfn 连续。
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

// 把宗教 c 的第 idx 个坐标写成 val（val 为 0 表示清除）。
void point_set(int c, int node, int l, int r, int idx, int val) {
    int p = base[c] + node;
    if (l == r) {
        seg_sum[p] = val;
        seg_max[p] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (idx <= mid) {
        point_set(c, node << 1, l, mid, idx, val);
    } else {
        point_set(c, node << 1 | 1, mid + 1, r, idx, val);
    }
    int lp = base[c] + (node << 1);
    int rp = lp + 1;
    seg_sum[p] = seg_sum[lp] + seg_sum[rp];
    seg_max[p] = max(seg_max[lp], seg_max[rp]);
}

// 在宗教 c 的线段树上查内部下标区间 [ql, qr] 的和与最大值。
void range_query(int c, int node, int l, int r, int ql, int qr, int &tsum, int &tmax) {
    if (ql <= l && r <= qr) {
        int p = base[c] + node;
        tsum += seg_sum[p];
        tmax = max(tmax, seg_max[p]);
        return;
    }
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        range_query(c, node << 1, l, mid, ql, qr, tsum, tmax);
    }
    if (qr > mid) {
        range_query(c, node << 1 | 1, mid + 1, r, ql, qr, tsum, tmax);
    }
}

// 把 dfn 值 d 在宗教 c 的坐标表里定位成内部下标；不在表里返回 0。
int find_index(int c, int d) {
    int p = lower_bound(pos[c].begin(), pos[c].end(), d) - pos[c].begin();
    if (p == (int)pos[c].size() || pos[c][p] != d) {
        return 0;
    }
    return p + 1;
}

// 在宗教 rel 的树上前缀查询路径 x -> y：先按 HLD 拆段，每段再换成内部下标区间。
void path_query(int x, int y, int rel, int &tsum, int &tmax) {
    while (top[x] != top[y]) {
        if (depth[top[x]] < depth[top[y]]) {
            swap(x, y);
        }
        int l = lower_bound(pos[rel].begin(), pos[rel].end(), dfn[top[x]]) - pos[rel].begin() + 1;
        int r = upper_bound(pos[rel].begin(), pos[rel].end(), dfn[x]) - pos[rel].begin();
        if (l <= r) {
            range_query(rel, 1, 1, kcnt[rel], l, r, tsum, tmax);
        }
        x = parent_[top[x]];
    }
    if (depth[x] > depth[y]) {
        swap(x, y);
    }
    int l = lower_bound(pos[rel].begin(), pos[rel].end(), dfn[x]) - pos[rel].begin() + 1;
    int r = upper_bound(pos[rel].begin(), pos[rel].end(), dfn[y]) - pos[rel].begin();
    if (l <= r) {
        range_query(rel, 1, 1, kcnt[rel], l, r, tsum, tmax);
    }
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
    for (int i = 1; i <= q; i++) {
        cin >> ops[i].type >> ops[i].x >> ops[i].y;
    }

    dfs1(1, 0);
    dfs2(1, 1);

    // 第一遍离线：按当前宗教把每个城市可能出现过的 dfn 收集起来。
    for (int i = 1; i <= n; i++) {
        cur[i] = col[i];
        pos[cur[i]].push_back(dfn[i]);
    }
    for (int i = 1; i <= q; i++) {
        if (ops[i].type[0] == 'C' && ops[i].type[1] == 'C') {
            cur[ops[i].x] = ops[i].y;
            pos[cur[ops[i].x]].push_back(dfn[ops[i].x]);
        }
    }

    // 每个宗教排序去重、分配一段连续节点池
    int used = 0;
    for (int c = 1; c < MAXC; c++) {
        if (pos[c].empty()) {
            continue;
        }
        sort(pos[c].begin(), pos[c].end());
        pos[c].erase(unique(pos[c].begin(), pos[c].end()), pos[c].end());
        kcnt[c] = (int)pos[c].size();
        base[c] = used;
        used += 4 * kcnt[c] + 4; // 普通线段树开 4 倍大小
    }
    seg_sum.assign(used, 0);
    seg_max.assign(used, 0);

    // 初始状态：把每个城市的评级写进它宗教树里对应的坐标
    for (int i = 1; i <= n; i++) {
        point_set(col[i], 1, 1, kcnt[col[i]], find_index(col[i], dfn[i]), w[i]);
    }

    // 第二遍在线：按顺序处理操作
    for (int i = 1; i <= q; i++) {
        int x = ops[i].x;
        int y = ops[i].y;
        char t0 = ops[i].type[0];
        char t1 = ops[i].type[1];
        if (t0 == 'C' && t1 == 'C') {
            int c = col[x];
            point_set(c, 1, 1, kcnt[c], find_index(c, dfn[x]), 0);
            col[x] = y;
            point_set(y, 1, 1, kcnt[y], find_index(y, dfn[x]), w[x]);
        } else if (t0 == 'C') {
            w[x] = y;
            int c = col[x];
            point_set(c, 1, 1, kcnt[c], find_index(c, dfn[x]), y);
        } else {
            int tsum = 0;
            int tmax = 0;
            path_query(x, y, col[x], tsum, tmax);
            if (t0 == 'Q' && t1 == 'S') {
                cout << tsum << '\n';
            } else {
                cout << tmax << '\n';
            }
        }
    }

    return 0;
}
