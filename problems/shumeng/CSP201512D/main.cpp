/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:57
 */
#include <bits/stdc++.h>
using namespace std;

struct Edge { int to, id; };
bool compare_edge(const Edge &left, const Edge &right) { return left.to < right.to; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<Edge> > graph(n + 1);
    vector<int> degree(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back({v, i}); graph[v].push_back({u, i});
        degree[u]++; degree[v]++;
    }
    int odd = 0;
    for (int i = 1; i <= n; i++) if (degree[i] % 2) odd++;
    if (odd != 0 && odd != 2 || (odd == 2 && degree[1] % 2 == 0)) {
        cout << -1 << '\n'; return 0;
    }
    for (int i = 1; i <= n; i++) sort(graph[i].begin(), graph[i].end(), compare_edge);
    vector<int> used(m), pointer(n + 1), stack_nodes, path;
    stack_nodes.push_back(1);
    while (!stack_nodes.empty()) {
        int u = stack_nodes.back();
        while (pointer[u] < (int)graph[u].size() && used[graph[u][pointer[u]].id]) pointer[u]++;
        if (pointer[u] == (int)graph[u].size()) {
            path.push_back(u); stack_nodes.pop_back();
        } else {
            Edge edge = graph[u][pointer[u]++];
            used[edge.id] = 1; stack_nodes.push_back(edge.to);
        }
    }
    if ((int)path.size() != m + 1) { cout << -1 << '\n'; return 0; }
    reverse(path.begin(), path.end());
    for (int i = 0; i < (int)path.size(); i++) cout << (i ? " " : "") << path[i];
    cout << '\n';
    return 0;
}
