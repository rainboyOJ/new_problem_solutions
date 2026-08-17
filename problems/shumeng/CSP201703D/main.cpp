/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:48
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXM = 200005;

struct Edge {
    int u, v, cost;
};

int parent[MAXN]; // 并查集父节点
Edge edges[MAXM];

// 路径压缩的并查集查找
int find_root(int x) {
    if (parent[x] == x) {
        return x;
    }
    parent[x] = find_root(parent[x]);
    return parent[x];
}

bool compare_edge(const Edge &left, const Edge &right) {
    return left.cost < right.cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
    }
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].cost;
    }
    if (n == 1) {
        cout << 0 << '\n';
        return 0;
    }

    // 按工期从小到大加入隧道，1 与 n 首次连通时的当前工期就是答案。
    // 若用不超过 w 的所有隧道能使 1、n 连通，则存在一条最大段长不超过 w 的线路。
    sort(edges + 1, edges + m + 1, compare_edge);
    for (int i = 1; i <= m; i++) {
        int x = find_root(edges[i].u);
        int y = find_root(edges[i].v);
        if (x != y) {
            parent[x] = y;
        }
        if (find_root(1) == find_root(n)) {
            cout << edges[i].cost << '\n';
            return 0;
        }
    }

    return 0;
}