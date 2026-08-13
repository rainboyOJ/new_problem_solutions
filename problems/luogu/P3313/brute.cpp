/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:59
 * update_at: 2026-08-12 23:00
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 查询时沿路径逐点向上爬，只统计与起点同宗教的城市评级。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, q;
int w[MAXN];    // w[i] 城市 i 的评级
int col[MAXN];  // col[i] 城市 i 的宗教

vector<int> g[MAXN]; // 树的邻接表

int parent[MAXN]; // 以 1 为根的父亲
int depth[MAXN];  // 深度

// 从根 1 出发 BFS，得到每个节点的父亲与深度，供路径逐点爬使用。
void build_root(int root) {
    queue<int> que;
    que.push(root);
    parent[root] = 0;
    depth[root] = 1;
    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (int v : g[u]) {
            if (v == parent[u]) continue;
            parent[v] = u;
            depth[v] = depth[u] + 1;
            que.push(v);
        }
    }
}

// 朴素路径查询：让较深的端点不断向上爬，逐点判断宗教是否相同。
// 爬的过程中把符合条件的评级累加进和、更新最大值。
void path_query(int x, int y, int rel, int &tsum, int &tmax) {
    while (depth[x] > depth[y]) {
        if (col[x] == rel) {
            tsum += w[x];
            tmax = max(tmax, w[x]);
        }
        x = parent[x];
    }
    while (depth[y] > depth[x]) {
        if (col[y] == rel) {
            tsum += w[y];
            tmax = max(tmax, w[y]);
        }
        y = parent[y];
    }
    // 现在 x、y 同深度，一起向上爬直到相遇。
    while (x != y) {
        if (col[x] == rel) {
            tsum += w[x];
            tmax = max(tmax, w[x]);
        }
        if (col[y] == rel) {
            tsum += w[y];
            tmax = max(tmax, w[y]);
        }
        x = parent[x];
        y = parent[y];
    }
    // x == y，是路径的公共祖先，只统计一次。
    if (col[x] == rel) {
        tsum += w[x];
        tmax = max(tmax, w[x]);
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

    build_root(1);

    while (q--) {
        string op;
        int x, y;
        cin >> op >> x >> y;
        if (op == "CC") {
            col[x] = y;
        } else if (op == "CW") {
            w[x] = y;
        } else {
            int tsum = 0, tmax = 0;
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
