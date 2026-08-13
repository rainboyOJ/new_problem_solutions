/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:59
 * update_at: 2026-08-12 22:59
 */
// P2680 [NOIP 2015 提高组] 运输计划
// 算法：二分答案 + 倍增 LCA + 树上边差分
// 判定 limit 可行：所有原长度 > limit 的路径必须被同一条边缩短，
// 该边必须被这些超标路径全部经过，且边权 >= 最长超标路径的缺口。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;
const int MAXM = 600005;
const int LOG = 20; // 2^19 = 524288 > 3e5，倍增层数取 LOG 足够覆盖树高

struct Query {
    int u, v, lca_node;
    long long length; // 第 i 个计划的原始路径长度
};

int n, m;
int head[MAXN], to[MAXM], nxt[MAXM], edge_weight[MAXM], edge_cnt;
int depth_node[MAXN];
int up[MAXN][LOG + 1]; // up[u][j] 表示 u 的 2^j 级祖先
int parent_edge_weight[MAXN]; // parent_edge_weight[u] 表示边 (parent[u], u) 的权值
long long dist_root[MAXN];    // dist_root[u] 表示根到 u 的路径长度
int diff_count[MAXN];         // check() 中使用的边差分计数
int bfs_order[MAXN], order_cnt; // BFS 顺序，反向遍历等价于自底向上汇总
Query query_data[MAXN];

// 链式前向星加一条边。
void add_edge(int u, int v, int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    edge_weight[edge_cnt] = w;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

// BFS 建树：求出深度、倍增祖先表、根到点的距离和父边权值。
// 用 BFS 而不是 DFS，避免 3e5 深度的递归爆栈。
void build_lca() {
    queue<int> que;
    que.push(1);
    depth_node[1] = 1;
    order_cnt = 0;

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        bfs_order[++order_cnt] = u;

        // 倍增转移：先跳 2^(j-1)，再跳 2^(j-1)。
        for (int j = 1; j <= LOG; j++) {
            up[u][j] = up[up[u][j - 1]][j - 1];
        }

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (v == up[u][0]) {
                continue;
            }
            up[v][0] = u;
            depth_node[v] = depth_node[u] + 1;
            dist_root[v] = dist_root[u] + edge_weight[i];
            parent_edge_weight[v] = edge_weight[i];
            que.push(v);
        }
    }
}

// 倍增求 lca(u, v)：先让深的点提到同一层，再同时向上跳。
int lca(int x, int y) {
    if (depth_node[x] < depth_node[y]) {
        swap(x, y);
    }

    int diff = depth_node[x] - depth_node[y];
    for (int j = LOG; j >= 0; j--) {
        if ((diff & (1 << j)) != 0) {
            x = up[x][j];
        }
    }

    if (x == y) {
        return x;
    }

    for (int j = LOG; j >= 0; j--) {
        if (up[x][j] != up[y][j]) {
            x = up[x][j];
            y = up[y][j];
        }
    }

    return up[x][0];
}

// 判断时间上限 limit 是否可行。
bool check(long long limit) {
    for (int i = 1; i <= n; i++) {
        diff_count[i] = 0;
    }

    int bad_count = 0;         // 原长度超过 limit 的超标路径条数
    long long need_reduce = 0; // 最长超标路径至少需要被缩短的量

    // 只统计超标路径。若一条超标路径不经过虫洞边，它不会变短，仍然超标。
    for (int i = 1; i <= m; i++) {
        if (query_data[i].length <= limit) {
            continue;
        }

        bad_count++;
        need_reduce = max(need_reduce, query_data[i].length - limit);

        // 边差分：路径 u -> v 的边覆盖次数整体 +1。
        // 端点处 +1、lca 处 -2，自底向上汇总后即得每条边的覆盖次数。
        int u = query_data[i].u;
        int v = query_data[i].v;
        int g = query_data[i].lca_node;
        diff_count[u]++;
        diff_count[v]++;
        diff_count[g] -= 2;
    }

    // 没有超标路径，当前 limit 已经可行。
    if (bad_count == 0) {
        return true;
    }

    long long best_common_edge = 0; // 所有超标路径公共边中的最大边权

    // 反向 BFS 序：先处理叶子，把儿子的差分值累加到父亲。
    // 汇总后 diff_count[x] 表示边 (parent[x], x) 被多少条超标路径覆盖。
    for (int i = order_cnt; i >= 1; i--) {
        int u = bfs_order[i];
        if (up[u][0] != 0 && diff_count[u] == bad_count) {
            // 这条边被所有超标路径共同经过，是虫洞的候选边。
            best_common_edge = max(best_common_edge, (long long)parent_edge_weight[u]);
        }
        if (up[u][0] != 0) {
            diff_count[up[u][0]] += diff_count[u];
        }
    }

    // 把候选公共边中权值最大的变成虫洞后，所有超标路径同时缩短该边权。
    // 可行当且仅当它不小于最长超标路径的缺口。
    return best_common_edge >= need_reduce;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    build_lca();

    // 读入计划，同时预处理每条计划的 lca 与原始长度。
    long long right_bound = 0;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        int g = lca(u, v);
        long long len = dist_root[u] + dist_root[v] - 2LL * dist_root[g];
        query_data[i] = {u, v, g, len};
        right_bound = max(right_bound, len);
    }

    // 二分最小可行时间：答案在 [0, 最长路径长度] 内单调可行。
    long long left = 0, right = right_bound;
    while (left < right) {
        long long mid = (left + right) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    cout << left << '\n';
    return 0;
}
