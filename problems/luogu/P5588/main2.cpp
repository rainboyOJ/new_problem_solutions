/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:30
 * update_at: 2026-10-26 17:15
 */
// main2.cpp：对每种颜色，先找同色节点集合的直径端点（树上任意点出发的最远
// 点一定是直径端点，扫描两次即可），再判断全部同色节点是否都落在直径路径
// 上；共线时答案等于"切断直径两端各第一条边后，两个外侧连通块大小相乘"。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005; // n <= 10^6

int n;
int color[MAXN]; // color[i]：节点 i 的颜色

vector<int> g[MAXN]; // g[u]：与 u 相邻的所有点

int parent[MAXN]; // 树上父亲（根 1 的父亲为 0）
int depth[MAXN];  // 节点深度（根为 0）
int order[MAXN];  // 从根出发的 BFS 顺序
int subtree[MAXN]; // subtree[u]：以 u 为根的子树大小

const int MAXLOG = 21; // 2^20 > 10^6，倍增层数上限
int up[MAXN][MAXLOG];  // up[x][k]：x 向上跳 2^k 步到达的祖先
int LOG;               // 实际用到的倍增层数，满足 2^LOG > n

vector<int> color_nodes[MAXN]; // color_nodes[c]：颜色 c 的所有节点
int color_count[MAXN];         // 每种颜色的节点个数

long long ans[MAXN];  // 每种颜色的答案

// 快读：n 可达 10^6，用 getchar 手写读整数更稳。
int read_int() {
    int x = 0;
    char c = getchar();
    while (c < '0' || c > '9') {
        c = getchar();
    }
    while (c >= '0' && c <= '9') {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x;
}

// 从根 1 出发 BFS，求出父亲、深度和 BFS 顺序（迭代，避免百万深度递归爆栈）。
void bfs_build() {
    int tail = 0;
    order[tail++] = 1;
    parent[1] = 0;
    depth[1] = 0;
    for (int i = 0; i < tail; i++) {
        int u = order[i];
        for (int v : g[u]) {
            if (v != parent[u]) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                order[tail++] = v;
            }
        }
    }
}

// 节点 x 向上跳 steps 步。
int jump(int x, int steps) {
    for (int k = 0; steps > 0; k++) {
        if (steps & 1) {
            x = up[x][k];
        }
        steps >>= 1;
    }
    return x;
}

// 求 x、y 的最近公共祖先（倍增 LCA）。
int lca(int x, int y) {
    if (depth[x] < depth[y]) {
        swap(x, y);
    }
    x = jump(x, depth[x] - depth[y]);
    if (x == y) {
        return x;
    }
    for (int k = LOG - 1; k >= 0; k--) {
        if (up[x][k] != up[y][k]) {
            x = up[x][k];
            y = up[y][k];
        }
    }
    return parent[x];
}

// 树上两点距离。
int dist(int x, int y) {
    int a = lca(x, y);
    return depth[x] + depth[y] - 2 * depth[a];
}

// 切断从 x 朝向 y 的第一条边后，x 所在连通块的大小。
long long side_size(int x, int y) {
    int a = lca(x, y);
    if (a == x) {
        // y 在 x 的子树里：把 y 上跳到 x 的直接儿子 child。
        int child = jump(y, depth[y] - depth[x] - 1);
        return n - subtree[child]; // x 那一侧 = 整棵树去掉 child 的子树
    }
    return subtree[x];
}

// 求颜色 c 的节点集合的直径端点。要求该颜色至少有一个节点。
// 两次最远点扫描：从任意同色点出发找到最远点 a，再从 a 找到最远点 b，(a, b) 即直径端点。
pair<int, int> color_diameter(int c) {
    int start = color_nodes[c][0];
    int far1 = start;
    int best = -1;
    for (int x : color_nodes[c]) {
        int d = dist(start, x);
        if (d > best) {
            best = d;
            far1 = x;
        }
    }
    int far2 = far1;
    best = -1;
    for (int x : color_nodes[c]) {
        int d = dist(far1, x);
        if (d > best) {
            best = d;
            far2 = x;
        }
    }
    return make_pair(far1, far2);
}

// 判断颜色 c 的所有节点是否都落在路径 a-b 上。
// 点在路径上当且仅当 dist(a,x) + dist(x,b) == dist(a,b)，这里 dia 就是该值。
bool all_on_path(int c, int a, int b, int dia) {
    for (int x : color_nodes[c]) {
        if (dist(a, x) + dist(x, b) != dia) {
            return false;
        }
    }
    return true;
}

int main() {
    n = read_int();
    for (int i = 1; i <= n; i++) {
        color[i] = read_int();
    }
    for (int i = 1; i < n; i++) {
        int u = read_int();
        int v = read_int();
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bfs_build();

    // 子树大小：所有叶子先为 1，按 BFS 逆序累加到父亲（深度大的先算）。
    for (int i = 1; i <= n; i++) {
        subtree[i] = 1;
    }
    for (int i = n - 1; i >= 1; i--) {
        subtree[parent[order[i]]] += subtree[order[i]];
    }

    // 倍增祖先表：up[x][k] = up[ up[x][k-1] ][k-1]。
    LOG = 0;
    while ((1 << LOG) <= n) {
        LOG++;
    }
    for (int x = 1; x <= n; x++) {
        up[x][0] = parent[x];
    }
    for (int k = 1; k < LOG; k++) {
        for (int x = 1; x <= n; x++) {
            up[x][k] = up[up[x][k - 1]][k - 1];
        }
    }

    // 按颜色把节点分组：color_nodes[c] 存颜色 c 的所有节点。
    for (int x = 1; x <= n; x++) {
        int c = color[x];
        color_nodes[c].push_back(x);
        color_count[c]++;
    }

    long long all_pairs = 1LL * n * (n - 1) / 2; // 全部无序点对
    for (int c = 1; c <= n; c++) {
        ans[c] = all_pairs; // 没有该颜色节点时，所有点对都合法
    }

    for (int c = 1; c <= n; c++) {
        if (color_count[c] == 0) {
            continue;
        }

        if (color_count[c] == 1) {
            // 只有一个同色节点 x：路径必须经过 x，即两端点落在 T - x 的
            // 不同连通块里。用补集：总数减去两端点在同一连通块的点对。
            int x = color_nodes[c][0];
            long long excluded = 1LL * (n - subtree[x]) * (n - subtree[x] - 1) / 2;
            for (int v : g[x]) {
                if (parent[v] == x) {
                    long long s = subtree[v];
                    excluded += s * (s - 1) / 2;
                }
            }
            ans[c] = all_pairs - excluded;
            continue;
        }

        // 多个同色节点：先求同色点集合的直径端点，再检查它们是否都在直径路径上。
        pair<int, int> ends = color_diameter(c);
        int a = ends.first;
        int b = ends.second;
        int dia = dist(a, b);

        if (all_on_path(c, a, b, dia)) {
            // 路径要包含整条 a-b，等价于两端点分居两个外侧连通块。
            ans[c] = side_size(a, b) * side_size(b, a);
        } else {
            ans[c] = 0; // 同色节点不共线，任何一条路径都装不下
        }
    }

    for (int c = 1; c <= n; c++) {
        printf("%lld\n", ans[c]);
    }

    return 0;
}
