/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 19:13
 * update_at: 2026-10-09 19:13
 */
// main.cpp：P5318 查找文献。
// 代码分层：读入 / 建图排序 / DFS / BFS 各一个函数，main 只按顺序调用；
// 图、访问标记这些核心数据放全局，函数之间共享，比一大段 main 清楚。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n, m; // 文章数（点）和引用关系数（边）

// g[u]：文章 u 引用的所有文章编号，按编号升序（编号 ≤ 1e5，用 int 存）
vector<vector<int>> g;
vector<int> visited; // visited[u]：0 表示这篇文章还没看过，1 表示已经看过

// 读入 n、m 和 m 条引用关系，建出邻接表
void read_input() {
    cin >> n >> m;

    g.assign(n + 1, vector<int>());
    for (ll i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
    }
}

// 每个点的引用列表按编号升序排好，之后才能保证“先看编号小的文章”
void build_graph() {
    for (ll u = 1; u <= n; u++) {
        sort(g[u].begin(), g[u].end());
    }
}

// 非递归 DFS：手工栈模拟递归，避免 n = 1e5 时递归爆栈
void dfs_solve() {
    visited.assign(n + 1, 0);

    stack<int> st;
    st.push(1); // 起点是 1 号文章

    while (!st.empty()) {
        int u = st.top();
        st.pop();
        if (visited[u] == 1) {
            continue; // 这个点更早的时候已经被访问过了
        }
        visited[u] = 1;
        cout << u << ' ';

        // 引用列表是升序的，从最后一条往前压栈，编号小的邻居后进栈、先弹出
        ll deg = g[u].size();
        for (ll i = deg - 1; i >= 0; i--) {
            int v = g[u][i];
            if (visited[v] == 0) {
                st.push(v);
            }
        }
    }
    cout << '\n';
}

// BFS：普通队列按层扩展，每层按编号升序入队
void bfs_solve() {
    visited.assign(n + 1, 0);

    queue<int> q;
    q.push(1);
    visited[1] = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << ' ';

        ll deg = g[u].size();
        for (ll i = 0; i < deg; i++) {
            int v = g[u][i];
            if (visited[v] == 0) {
                visited[v] = 1;
                q.push(v);
            }
        }
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    build_graph();
    dfs_solve();
    bfs_solve();

    return 0;
}
