#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;
const int MAXE = 1000005;
const int LOG = 20;

int n, m, root;
int head[MAXN], to[MAXE], nxt[MAXE], edge_cnt;
int depth_node[MAXN];
int up[MAXN][LOG + 1];

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void read_input() {
    cin >> n >> m >> root;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
        add_edge(v, u);
    }
}

void build_lca() {
    queue<int> que;
    que.push(root);
    depth_node[root] = 1;
    up[root][0] = 0;

    while (!que.empty()) {
        int u = que.front();
        que.pop();

        for (int j = 1; j <= LOG; j++) {
            up[u][j] = up[up[u][j - 1]][j - 1];
        }

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            if (v == up[u][0]) {
                continue;
            }
            up[v][0] = u;
            depth_node[v] = depth_node[u] + 1;
            que.push(v);
        }
    }
}

int lca(int x, int y) {
    if (depth_node[x] < depth_node[y]) {
        swap(x, y);
    }

    int diff = depth_node[x] - depth_node[y];
    for (int j = LOG; j >= 0; j--) {
        if ((diff & (1 << j)) != 0) {
            x = up[x][j];
        }
    }

    if (x == y) {
        return x;
    }

    for (int j = LOG; j >= 0; j--) {
        if (up[x][j] != up[y][j]) {
            x = up[x][j];
            y = up[y][j];
        }
    }

    return up[x][0];
}

void solve() {
    build_lca();

    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        cout << lca(x, y) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
