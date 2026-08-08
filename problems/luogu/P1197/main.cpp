#include <bits/stdc++.h>
using namespace std;

const int MAXN = 400005;
const int MAXM = 200005;

struct Edge {
    int u;
    int v;
};

int n, m, k;
Edge edges[MAXM];
vector<int> graph_edges[MAXN];
int destroy_order[MAXN];
bool destroyed[MAXN], active_node[MAXN];
int fa[MAXN], sz[MAXN];
int answer[MAXN];
int components;

void init_dsu() {
    for (int i = 0; i < n; i++) {
        fa[i] = i;
        sz[i] = 1;
    }
}

int find_set(int x) {
    while (fa[x] != x) {
        fa[x] = fa[fa[x]];
        x = fa[x];
    }
    return x;
}

void unite_set(int x, int y) {
    int fx = find_set(x);
    int fy = find_set(y);
    if (fx == fy) {
        return;
    }
    if (sz[fx] < sz[fy]) {
        swap(fx, fy);
    }
    fa[fy] = fx;
    sz[fx] += sz[fy];
    components--;
}

void add_planet(int u) {
    active_node[u] = true;
    components++;
    for (int i = 0; i < (int)graph_edges[u].size(); i++) {
        int v = graph_edges[u][i];
        if (active_node[v]) {
            unite_set(u, v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v;
        graph_edges[edges[i].u].push_back(edges[i].v);
        graph_edges[edges[i].v].push_back(edges[i].u);
    }

    cin >> k;
    for (int i = 1; i <= k; i++) {
        cin >> destroy_order[i];
        destroyed[destroy_order[i]] = true;
    }

    init_dsu();
    components = 0;
    for (int i = 0; i < n; i++) {
        if (!destroyed[i]) {
            add_planet(i);
        }
    }

    answer[k + 1] = components;
    for (int i = k; i >= 1; i--) {
        add_planet(destroy_order[i]);
        answer[i] = components;
    }

    for (int i = 1; i <= k + 1; i++) {
        cout << answer[i] << '\n';
    }

    return 0;
}
