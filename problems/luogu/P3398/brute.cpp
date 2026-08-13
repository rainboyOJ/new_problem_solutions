/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:59
 * update_at: 2026-08-12 22:59
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 每次询问先求出树上的父关系与深度，再：
//   1) 从 a 爬到 b，把路径 a-b 上的所有点标记为 1；
//   2) 从 c 爬到 d，沿途检查是否遇到被标记过的点。
// 每条路径用「两个端点同时向上爬」实现，复杂度 O(路径长度)，只适合小数据。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, q;
vector<int> g[MAXN]; // 树的邻接表
int parent[MAXN];    // parent[u] 表示 u 的父节点（根 1 的父节点是 0）
int depth[MAXN];     // depth[u] 表示 u 的深度
bool mark[MAXN];     // mark[u] = true 表示 u 在路径 a-b 上

// 从根 1 出发求父节点和深度（暴力爬路径需要）。
void get_parent() {
    queue<int> que;
    que.push(1);
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

// 把路径 a-b 上经过的所有点标记为 true。
void mark_path(int a, int b) {
    int x = a, y = b;
    // 深的端点先单独向上爬，直到两个端点同深度。
    while (depth[x] > depth[y]) {
        mark[x] = true;
        x = parent[x];
    }
    while (depth[y] > depth[x]) {
        mark[y] = true;
        y = parent[y];
    }
    // 两个端点一起向上爬，爬到头时再标记相遇点。
    while (x != y) {
        mark[x] = true;
        mark[y] = true;
        x = parent[x];
        y = parent[y];
    }
    mark[x] = true;
}

// 从 c 爬到 d，检查路径上是否有被标记过的点（即与路径 a-b 相交）。
bool check_path(int c, int d) {
    int x = c, y = d;
    while (depth[x] > depth[y]) {
        if (mark[x]) return true;
        x = parent[x];
    }
    while (depth[y] > depth[x]) {
        if (mark[y]) return true;
        y = parent[y];
    }
    while (x != y) {
        if (mark[x] || mark[y]) return true;
        x = parent[x];
        y = parent[y];
    }
    return mark[x];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    get_parent();

    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        fill(mark, mark + n + 1, false); // 清空上次标记
        mark_path(a, b);
        if (check_path(c, d))
            cout << "Y\n";
        else
            cout << "N\n";
    }

    return 0;
}
