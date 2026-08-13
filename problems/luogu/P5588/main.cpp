/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:30
 * update_at: 2026-08-12 22:31
 */
// main.cpp：对每种颜色，先找同色节点集合的直径端点（树上任意点出发的最远
// 点一定是直径端点，扫描两次即可），再判断全部同色节点是否都落在直径路径
// 上；共线时答案等于"切断直径两端各第一条边后，两个外侧连通块大小相乘"。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005; // n <= 10^6

int n;
int color[MAXN]; // color[i]：节点 i 的颜色

int head[MAXN], to[MAXN * 2], nxt[MAXN * 2], edge_cnt; // 链式前向星存树

int parent[MAXN]; // 树上父亲（根 1 的父亲为 0）
int depth[MAXN];  // 节点深度（根为 0）
int order[MAXN];  // 从根出发的 BFS 顺序
int subtree[MAXN]; // subtree[u]：以 u 为根的子树大小

vector<vector<int>> up; // up[k][x]：x 向上跳 2^k 步到达的祖先

int color_head[MAXN]; // color_head[c]：颜色 c 的链表头节点
int next_same[MAXN];  // next_same[x]：与 x 同色的下一个节点
int color_count[MAXN]; // 每种颜色的节点个数

long long ans[MAXN];  // 每种颜色的答案

// 加一条无向边。
void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

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
        for (int e = head[u]; e != 0; e = nxt[e]) {
            int v = to[e];
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
            x = up[k][x];
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
    for (int k = (int)up.size() - 1; k >= 0; k--) {
        if (up[k][x] != up[k][y]) {
            x = up[k][x];
            y = up[k][y];
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

int main() {
    n = read_int();
    for (int i = 1; i <= n; i++) {
        color[i] = read_int();
    }
    for (int i = 1; i < n; i++) {
        int u = read_int();
        int v = read_int();
        add_edge(u, v);
        add_edge(v, u);
    }

    bfs_build();

    // 子树大小：所有叶子先为 1，按 BFS 逆序累加到父亲（深度大的先算）。
    for (int i = 1; i <= n; i++) {
        subtree[i] = 1;
    }
    for (int i = n - 1; i >= 1; i--) {
        subtree[parent[order[i]]] += subtree[order[i]];
    }

    // 倍增祖先表：up[k][x] = up[k-1][ up[k-1][x] ]。
    int LOG = 0;
    while ((1 << LOG) <= n) {
        LOG++;
    }
    up.resize(LOG);
    for (int k = 0; k < LOG; k++) {
        up[k].resize(n + 1);
    }
    for (int x = 1; x <= n; x++) {
        up[0][x] = parent[x];
    }
    for (int k = 1; k < LOG; k++) {
        for (int x = 1; x <= n; x++) {
            up[k][x] = up[k - 1][up[k - 1][x]];
        }
    }

    // 相同颜色的节点建成链表：color_head[c] -> next_same。
    for (int x = 1; x <= n; x++) {
        int c = color[x];
        next_same[x] = color_head[c];
        color_head[c] = x;
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
            int x = color_head[c];
            long long excluded = 1LL * (n - subtree[x]) * (n - subtree[x] - 1) / 2;
            for (int e = head[x]; e != 0; e = nxt[e]) {
                int v = to[e];
                if (parent[v] == x) {
                    long long s = subtree[v];
                    excluded += s * (s - 1) / 2;
                }
            }
            ans[c] = all_pairs - excluded;
            continue;
        }

        // 多个同色节点：两次最远点扫描求出同色点集合的直径端点。
        int first = color_head[c];
        int second = first;
        int best = -1;
        for (int x = first; x != 0; x = next_same[x]) {
            int d = dist(first, x);
            if (d > best) {
                best = d;
                second = x;
            }
        }
        int third = second;
        best = -1;
        for (int x = first; x != 0; x = next_same[x]) {
            int d = dist(second, x);
            if (d > best) {
                best = d;
                third = x;
            }
        }
        int dia = dist(second, third);

        // 检查全部同色节点是否都在直径路径 second-third 上。
        // 在路径上当且仅当 dist(second,x) + dist(x,third) == dia。
        bool lies_on_path = true;
        for (int x = first; x != 0; x = next_same[x]) {
            if (dist(second, x) + dist(x, third) != dia) {
                lies_on_path = false;
                break;
            }
        }

        if (lies_on_path) {
            // 路径要包含整条 second-third，等价于两端点分居两个外侧连通块。
            ans[c] = side_size(second, third) * side_size(third, second);
        } else {
            ans[c] = 0; // 同色节点不共线，任何一条路径都装不下
        }
    }

    for (int c = 1; c <= n; c++) {
        printf("%lld\n", ans[c]);
    }

    return 0;
}
