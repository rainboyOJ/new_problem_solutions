// brute.cpp：小图枚举所有边集，按简单环定义直接检查。
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
} edges[25];

int T;
int n, m;
int deg[20];
bool used_vertex[20];
vector<int> graph[20];

unsigned long long best_value;
vector<int> best_edges;

bool is_simple_cycle(int mask, vector<int> &picked_edges) {
    for (int i = 1; i <= n; i++) {
        deg[i] = 0;
        used_vertex[i] = false;
        graph[i].clear();
    }

    picked_edges.clear();

    for (int i = 1; i <= m; i++) {
        if (((mask >> (i - 1)) & 1) == 0) {
            continue;
        }
        int u = edges[i].u;
        int v = edges[i].v;
        deg[u]++;
        deg[v]++;
        used_vertex[u] = true;
        used_vertex[v] = true;
        graph[u].push_back(v);
        graph[v].push_back(u);
        picked_edges.push_back(i);
    }

    int vertex_cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!used_vertex[i]) {
            continue;
        }
        vertex_cnt++;
        if (deg[i] != 2) {
            return false;
        }
    }

    if (vertex_cnt < 3) {
        return false;
    }
    if ((int)picked_edges.size() != vertex_cnt) {
        return false;
    }

    queue<int> q;
    bool vis[20] = {false};
    int start = 0;
    for (int i = 1; i <= n; i++) {
        if (used_vertex[i]) {
            start = i;
            break;
        }
    }

    q.push(start);
    vis[start] = true;
    int reached = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        reached++;

        for (int v : graph[u]) {
            if (vis[v]) {
                continue;
            }
            vis[v] = true;
            q.push(v);
        }
    }

    return reached == vertex_cnt;
}

void solve_one_case() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v;
    }

    best_value = numeric_limits<unsigned long long>::max();
    best_edges.clear();

    vector<int> picked_edges;
    int total_mask = 1 << m;
    for (int mask = 0; mask < total_mask; mask++) {
        if (!is_simple_cycle(mask, picked_edges)) {
            continue;
        }

        unsigned long long value = 0;
        for (int id : picked_edges) {
            value += (1ULL << id);
        }

        if (value < best_value) {
            best_value = value;
            best_edges = picked_edges;
        }
    }

    if (best_edges.empty()) {
        cout << -1 << '\n';
        return;
    }

    sort(best_edges.begin(), best_edges.end());
    for (int i = 0; i < (int)best_edges.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << best_edges[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        solve_one_case();
    }

    return 0;
}
