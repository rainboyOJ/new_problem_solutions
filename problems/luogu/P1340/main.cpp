#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

struct Edge {
    int u, v, w;
};

int n, weeks;
vector<Edge> forest;
long long total_weight = 0;

vector<pair<int, int>> graph[MAXN];
bool vis[MAXN];
int parent_node[MAXN];
int parent_edge[MAXN];

void build_graph() {
    for (int i = 1; i <= n; i++) {
        graph[i].clear();
    }
    for (int i = 0; i < (int)forest.size(); i++) {
        Edge &e = forest[i];
        graph[e.u].push_back({e.v, i});
        graph[e.v].push_back({e.u, i});
    }
}

// 如果 u 和 v 当前在同一棵树里，返回路径上权值最大的边编号。
// 否则返回 -1，表示这条新边会连接两个不同连通块。
int max_edge_on_path(int start, int target) {
    build_graph();
    for (int i = 1; i <= n; i++) {
        vis[i] = false;
        parent_node[i] = 0;
        parent_edge[i] = -1;
    }

    queue<int> q;
    q.push(start);
    vis[start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == target) {
            break;
        }

        for (pair<int, int> e : graph[u]) {
            int v = e.first;
            int id = e.second;
            if (vis[v]) {
                continue;
            }
            vis[v] = true;
            parent_node[v] = u;
            parent_edge[v] = id;
            q.push(v);
        }
    }

    if (!vis[target]) {
        return -1;
    }

    int best_id = -1;
    int cur = target;
    while (cur != start) {
        int id = parent_edge[cur];
        if (best_id == -1 || forest[id].w > forest[best_id].w) {
            best_id = id;
        }
        cur = parent_node[cur];
    }

    return best_id;
}

void add_new_edge(Edge e) {
    int id = max_edge_on_path(e.u, e.v);

    if (id == -1) {
        forest.push_back(e);
        total_weight += e.w;
        return;
    }

    if (forest[id].w > e.w) {
        total_weight += e.w - forest[id].w;
        forest[id] = e;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> weeks;

    for (int i = 1; i <= weeks; i++) {
        Edge e;
        cin >> e.u >> e.v >> e.w;
        add_new_edge(e);

        if ((int)forest.size() == n - 1) {
            cout << total_weight << '\n';
        } else {
            cout << -1 << '\n';
        }
    }

    return 0;
}
