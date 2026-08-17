/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:59
 */
// brute.cpp：小数据暴力解，枚举选择 n-1 条边并检查是否成树。
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u;
    int v;
    int cost;
};

int n, m;
vector<Edge> edges;
int choose_edge[25];
long long answer;

bool check_tree() {
    int parent[10];
    for (int i = 1; i <= n; i++) parent[i] = i;
    for (int i = 0; i < m; i++) {
        if (!choose_edge[i]) continue;
        int u = edges[i].u;
        int v = edges[i].v;
        while (parent[u] != u) u = parent[u];
        while (parent[v] != v) v = parent[v];
        if (u == v) return false;
        parent[u] = v;
    }
    int root = parent[1];
    while (parent[root] != root) root = parent[root];
    for (int i = 2; i <= n; i++) {
        int current = i;
        while (parent[current] != current) current = parent[current];
        if (current != root) return false;
    }
    return true;
}

void dfs(int pos, int selected, long long cost) {
    if (selected > n - 1 || selected + m - pos < n - 1) return;
    if (pos == m) {
        if (selected == n - 1 && check_tree()) answer = min(answer, cost);
        return;
    }
    choose_edge[pos] = 0;
    dfs(pos + 1, selected, cost);
    choose_edge[pos] = 1;
    dfs(pos + 1, selected + 1, cost + edges[pos].cost);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    edges.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].cost;
    }
    answer = (1LL << 60);
    dfs(0, 0, 0);
    cout << answer << '\n';
    return 0;
}
