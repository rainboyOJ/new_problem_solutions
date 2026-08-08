#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
const int MAXM = 300000 + 5;
const int MAXE = 2 * MAXN + 5;
const int LOG = 18;
const int INF = 0x3f3f3f3f;

struct Edge {
    int u, v, w;

    bool operator<(const Edge &other) const {
        return w > other.w;
    }
} edges[MAXM];

int n, m, q;

// 最大生成森林
int head[MAXN], to[MAXE], nxt[MAXE], wgt[MAXE], edge_cnt;

// 并查集
int fa[MAXN], siz[MAXN];

// 倍增 LCA
int depth_arr[MAXN];
int up[MAXN][LOG];
int min_edge[MAXN][LOG];  // 跳 2^j 层时路径上的最小边权
bool vis[MAXN];

void init_graph(int n) {
    edge_cnt = 0;
    for (int i = 1; i <= n; i++) {
        head[i] = 0;
        depth_arr[i] = 0;
        vis[i] = false;
        for (int j = 0; j < LOG; j++) {
            up[i][j] = 0;
            min_edge[i][j] = INF;
        }
    }
}

void add_edge(int u, int v, int w) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    wgt[edge_cnt] = w;
    head[u] = edge_cnt;
}

int find_root(int x) {
    if (fa[x] == x) {
        return x;
    }
    fa[x] = find_root(fa[x]);
    return fa[x];
}

bool unite(int x, int y) {
    x = find_root(x);
    y = find_root(y);
    if (x == y) {
        return false;
    }

    if (siz[x] < siz[y]) {
        swap(x, y);
    }
    fa[y] = x;
    siz[x] += siz[y];
    return true;
}

void build_forest() {
    for (int i = 1; i <= n; i++) {
        fa[i] = i;
        siz[i] = 1;
    }

    sort(edges + 1, edges + m + 1);

    for (int i = 1; i <= m; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (unite(u, v)) {
            add_edge(u, v, w);
            add_edge(v, u, w);
        }
    }
}

void build_lca() {
    vector<int> st;

    for (int root = 1; root <= n; root++) {
        if (vis[root]) {
            continue;
        }

        vis[root] = true;
        depth_arr[root] = 0;
        up[root][0] = 0;
        min_edge[root][0] = INF;
        st.push_back(root);

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();

            for (int i = head[u]; i != 0; i = nxt[i]) {
                int v = to[i];
                if (v == up[u][0]) {
                    continue;
                }

                vis[v] = true;
                depth_arr[v] = depth_arr[u] + 1;
                up[v][0] = u;
                min_edge[v][0] = wgt[i];

                for (int j = 1; j < LOG; j++) {
                    up[v][j] = up[up[v][j - 1]][j - 1];
                    min_edge[v][j] = min(min_edge[v][j - 1], min_edge[up[v][j - 1]][j - 1]);
                }

                st.push_back(v);
            }
        }
    }
}

int query(int x, int y) {
    if (find_root(x) != find_root(y)) {
        return -1;
    }

    int ans = INF;

    if (depth_arr[x] < depth_arr[y]) {
        swap(x, y);
    }

    int diff = depth_arr[x] - depth_arr[y];
    for (int j = 0; j < LOG; j++) {
        if (diff & (1 << j)) {
            ans = min(ans, min_edge[x][j]);
            x = up[x][j];
        }
    }

    if (x == y) {
        return ans;
    }

    for (int j = LOG - 1; j >= 0; j--) {
        if (up[x][j] != up[y][j]) {
            ans = min(ans, min_edge[x][j]);
            ans = min(ans, min_edge[y][j]);
            x = up[x][j];
            y = up[y][j];
        }
    }

    ans = min(ans, min_edge[x][0]);
    ans = min(ans, min_edge[y][0]);

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    init_graph(n);

    for (int i = 1; i <= m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    build_forest();
    build_lca();

    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << query(x, y) << '\n';
    }

    return 0;
}
