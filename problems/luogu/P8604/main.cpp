#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u;
    int v;
};

static vector<vector<pair<int, int>>> g;
static vector<Edge> edges;
static vector<int> dfn, low;
static vector<int> estack;
static vector<vector<int>> tree;
static vector<int> mark;
static int n, m;
static int dfs_clock = 0;
static int bcc_cnt = 0;

void tarjan(int u, int parent_edge) {
    dfn[u] = low[u] = ++dfs_clock;

    for (auto [v, id] : g[u]) {
        if (!dfn[v]) {
            estack.push_back(id);
            tarjan(v, id);
            low[u] = min(low[u], low[v]);

            if (low[v] >= dfn[u]) {
                ++bcc_cnt;
                int comp = n + bcc_cnt;
                vector<int> nodes;

                while (true) {
                    int eid = estack.back();
                    estack.pop_back();
                    int a = edges[eid].u;
                    int b = edges[eid].v;
                    if (!mark[a]) {
                        mark[a] = 1;
                        nodes.push_back(a);
                    }
                    if (!mark[b]) {
                        mark[b] = 1;
                        nodes.push_back(b);
                    }
                    if (eid == id) {
                        break;
                    }
                }

                for (int x : nodes) {
                    tree[comp].push_back(x);
                    tree[x].push_back(comp);
                    mark[x] = 0;
                }
            }
        } else if (id != parent_edge && dfn[v] < dfn[u]) {
            estack.push_back(id);
            low[u] = min(low[u], dfn[v]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    g.assign(n + 1, {});
    edges.resize(m);
    tree.assign(n + m + 5, {});
    mark.assign(n + 1, 0);
    dfn.assign(n + 1, 0);
    low.assign(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edges[i] = {u, v};
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }

    int x, y;
    cin >> x >> y;
    if (x == y) {
        cout << 0 << '\n';
        return 0;
    }

    for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            tarjan(i, -1);
        }
    }

    int tot = n + bcc_cnt;
    vector<int> parent(tot + 1, -1);
    queue<int> q;
    q.push(x);
    parent[x] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == y) {
            break;
        }
        for (int v : tree[u]) {
            if (parent[v] != -1) {
                continue;
            }
            parent[v] = u;
            q.push(v);
        }
    }

    if (parent[y] == -1) {
        cout << 0 << '\n';
        return 0;
    }

    int ans = 0;
    int cur = y;
    while (cur != x) {
        if (cur <= n && cur != x && cur != y) {
            ++ans;
        }
        cur = parent[cur];
    }

    cout << ans << '\n';
    return 0;
}
