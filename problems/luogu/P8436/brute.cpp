// brute.cpp：小数据暴力。
// 先枚举每条边判断它是不是桥，再删掉所有桥求连通块，这些连通块就是边双连通分量。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;
const int MAXM = 40;
const int MAXE = MAXM * 2 + 5;

struct Edge {
    int u, v;
} edges[MAXM];

int n, m;
int head[MAXN], to[MAXE], nxt[MAXE], edge_cnt;
bool vis[MAXN];
bool is_bridge[MAXM];
vector< vector<int> > answer;

void init_graph() {
    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = -1;
        vis[i] = false;
    }
}

void add_edge(int u, int v) {
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
    edge_cnt++;
}

void build_graph(int ban_edge, bool remove_bridges) {
    init_graph();
    for (int i = 1; i <= m; i++) {
        if (i == ban_edge) {
            continue;
        }
        if (remove_bridges && is_bridge[i]) {
            continue;
        }
        add_edge(edges[i].u, edges[i].v);
        add_edge(edges[i].v, edges[i].u);
    }
}

void dfs_count(int u) {
    vis[u] = true;
    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i];
        if (!vis[v]) {
            dfs_count(v);
        }
    }
}

int count_components(int ban_edge) {
    build_graph(ban_edge, false);

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            cnt++;
            dfs_count(i);
        }
    }
    return cnt;
}

void dfs_collect(int u, vector<int> &comp) {
    vis[u] = true;
    comp.push_back(u);

    for (int i = head[u]; i != -1; i = nxt[i]) {
        int v = to[i];
        if (!vis[v]) {
            dfs_collect(v, comp);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v;
        is_bridge[i] = false;
    }

    int base_cc = count_components(0);
    for (int i = 1; i <= m; i++) {
        int cc = count_components(i);
        if (cc > base_cc) {
            is_bridge[i] = true;
        }
    }

    build_graph(0, true);
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            vector<int> comp;
            dfs_collect(i, comp);
            answer.push_back(comp);
        }
    }

    cout << answer.size() << '\n';
    for (size_t i = 0; i < answer.size(); i++) {
        cout << answer[i].size();
        for (size_t j = 0; j < answer[i].size(); j++) {
            cout << ' ' << answer[i][j];
        }
        cout << '\n';
    }

    return 0;
}
