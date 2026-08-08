#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;
const int MAXV = MAXN * MAXN * 2 + 5;
const long long INF = (1LL << 60);

struct HeapNode {
    int u;
    long long dist;

    bool operator < (const HeapNode &other) const {
        return dist > other.dist;
    }
};

int n, m;
bool can_transfer[MAXN][MAXN];
int sx, sy, tx, ty;
vector<pair<int, int> > g[MAXV];
long long dist_arr[MAXV];
bool vis[MAXV];

int row_id(int x, int y) {
    return ((x - 1) * n + (y - 1)) * 2 + 1;
}

int col_id(int x, int y) {
    return ((x - 1) * n + (y - 1)) * 2 + 2;
}

void add_edge(int u, int v, int len) {
    g[u].push_back(make_pair(v, len));
}

void build_graph() {
    int tot = n * n * 2;
    for (int i = 1; i <= tot; i++) {
        g[i].clear();
    }

    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            if (y + 1 <= n) {
                add_edge(row_id(x, y), row_id(x, y + 1), 2);
                add_edge(row_id(x, y + 1), row_id(x, y), 2);
            }
            if (x + 1 <= n) {
                add_edge(col_id(x, y), col_id(x + 1, y), 2);
                add_edge(col_id(x + 1, y), col_id(x, y), 2);
            }

            if (can_transfer[x][y]) {
                add_edge(row_id(x, y), col_id(x, y), 1);
                add_edge(col_id(x, y), row_id(x, y), 1);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            can_transfer[i][j] = false;
        }
    }

    for (int i = 1; i <= m; i++) {
        int x, y;
        cin >> x >> y;
        can_transfer[x][y] = true;
    }

    cin >> sx >> sy >> tx >> ty;

    build_graph();

    int tot = n * n * 2;
    for (int i = 1; i <= tot; i++) {
        dist_arr[i] = INF;
        vis[i] = false;
    }

    priority_queue<HeapNode> pq;
    dist_arr[row_id(sx, sy)] = 0;
    dist_arr[col_id(sx, sy)] = 0;
    pq.push({row_id(sx, sy), 0});
    pq.push({col_id(sx, sy), 0});

    while (!pq.empty()) {
        HeapNode cur = pq.top();
        pq.pop();

        int u = cur.u;
        if (vis[u]) {
            continue;
        }
        vis[u] = true;

        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i].first;
            long long nd = dist_arr[u] + g[u][i].second;
            if (nd < dist_arr[v]) {
                dist_arr[v] = nd;
                pq.push({v, nd});
            }
        }
    }

    long long answer = min(dist_arr[row_id(tx, ty)], dist_arr[col_id(tx, ty)]);
    if (answer >= INF / 2) {
        cout << -1 << '\n';
    }
    else {
        cout << answer << '\n';
    }

    return 0;
}
