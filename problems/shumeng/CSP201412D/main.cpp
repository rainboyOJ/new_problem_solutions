/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:00
 */
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u;
    int v;
    int cost;
};

int parent_node[1005];

int find_root(int x) {
    if (parent_node[x] == x) return x;
    return parent_node[x] = find_root(parent_node[x]);
}

bool compare_edge(const Edge &left, const Edge &right) {
    return left.cost < right.cost;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].cost;
    }

    sort(edges.begin(), edges.end(), compare_edge);
    for (int i = 1; i <= n; i++) parent_node[i] = i;

    long long answer = 0;
    int selected = 0;
    for (int i = 0; i < m && selected < n - 1; i++) {
        int root_u = find_root(edges[i].u);
        int root_v = find_root(edges[i].v);
        if (root_u == root_v) continue;
        parent_node[root_u] = root_v;
        answer += edges[i].cost;
        selected++;
    }

    cout << answer << '\n';
    return 0;
}
