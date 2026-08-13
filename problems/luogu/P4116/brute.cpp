/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:59
 * update_at: 2026-08-12 22:59
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 每次查询从 v 沿父链一路爬到根，途中最靠近根的那个黑点就是路径上的第一个黑点。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, q;
vector<int> g[MAXN]; // 邻接表存树
int parent[MAXN];    // parent[u]：u 的父亲（根 1 的父亲为 0）
bool black[MAXN];    // black[u]：节点 u 当前是否为黑点

// 从根 1 做 BFS，求出每个节点的父亲。
void bfs_parent(int root) {
    queue<int> qu;
    qu.push(root);
    parent[root] = 0;
    while (!qu.empty()) {
        int u = qu.front();
        qu.pop();
        for (int j = 0; j < (int)g[u].size(); j++) {
            int v = g[u][j];
            if (v == parent[u]) continue;
            parent[v] = u;
            qu.push(v);
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

    bfs_parent(1);

    while (q--) {
        int op, x;
        cin >> op >> x;
        if (op == 0) {
            black[x] = !black[x];
        } else {
            // 沿父链从 x 爬到根，经过的节点正好是根到 x 的整条路径；
            // 遇到黑点就记录，最后一次记录的黑点最靠近根，就是第一个黑点。
            int ans = -1;
            for (int u = x; u != 0; u = parent[u]) {
                if (black[u]) ans = u;
            }
            cout << ans << '\n';
        }
    }

    return 0;
}
