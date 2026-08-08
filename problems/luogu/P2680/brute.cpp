#include <bits/stdc++.h>
using namespace std;

// brute.cpp：枚举哪一条边变成 0，再逐条路径 BFS 求长度，只适合小数据。

const int MAXN = 55;

struct EdgeInfo {
    int u, v, w;
};

struct AdjEdge {
    int to, id;
};

int n, m;
EdgeInfo edges[MAXN];
vector<AdjEdge> graph_edges[MAXN];
pair<int, int> queries[MAXN];
int parent_node[MAXN], parent_edge_id[MAXN];

int path_length_with_free_edge(int start, int target, int free_edge_id) {
    for (int i = 1; i <= n; i++) {
        parent_node[i] = -1;
        parent_edge_id[i] = 0;
    }

    queue<int> que;
    que.push(start);
    parent_node[start] = 0;

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        if (u == target) {
            break;
        }
        for (int i = 0; i < (int)graph_edges[u].size(); i++) {
            int v = graph_edges[u][i].to;
            int id = graph_edges[u][i].id;
            if (parent_node[v] == -1) {
                parent_node[v] = u;
                parent_edge_id[v] = id;
                que.push(v);
            }
        }
    }

    int length = 0;
    int x = target;
    while (x != start) {
        int id = parent_edge_id[x];
        if (id != free_edge_id) {
            length += edges[id].w;
        }
        x = parent_node[x];
    }
    return length;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i < n; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
        graph_edges[edges[i].u].push_back({edges[i].v, i});
        graph_edges[edges[i].v].push_back({edges[i].u, i});
    }

    for (int i = 1; i <= m; i++) {
        cin >> queries[i].first >> queries[i].second;
    }

    int answer = 1000000000;
    for (int free_edge_id = 1; free_edge_id < n; free_edge_id++) {
        int worst = 0;
        for (int i = 1; i <= m; i++) {
            int len = path_length_with_free_edge(queries[i].first, queries[i].second, free_edge_id);
            worst = max(worst, len);
        }
        answer = min(answer, worst);
    }

    cout << answer << '\n';

    return 0;
}
