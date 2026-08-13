/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:28
 * update_at: 2026-08-12 22:28
 */
#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，每次询问把 x 到根的路径整条标记出来，
// 再从 y 向上爬父亲，遇到的第一个已标记点就是最近公共祖先。
// 单次询问 O(n)，只适合小数据对拍和帮助理解题意。

const int MAXN = 105;

int n, m, root;
vector<int> g[MAXN];  // 邻接表
int fa[MAXN];         // fa[u] 表示 u 的父亲，根的父亲为 0
int vis[MAXN];        // 本次询问标记 x 的祖先路径

// BFS 求每个点的父亲（根的父亲为 0）。
void build_fa() {
    queue<int> que;
    que.push(root);
    fa[root] = 0;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (v == fa[u]) {
                continue;
            }
            fa[v] = u;
            que.push(v);
        }
    }
}

// 暴力求 x, y 的最近公共祖先。
int lca_brute(int x, int y) {
    // 从 x 一路向上走到根，沿途全部标记。
    while (x != 0) {
        vis[x] = 1;
        x = fa[x];
    }
    // 从 y 向上爬，第一个已被标记的点就是最近公共祖先。
    while (vis[y] == 0) {
        y = fa[y];
    }
    return y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> root;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    build_fa();

    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        memset(vis, 0, sizeof(vis));
        cout << lca_brute(x, y) << '\n';
    }

    return 0;
}
