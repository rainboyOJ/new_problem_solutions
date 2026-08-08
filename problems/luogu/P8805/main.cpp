#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
const int LOG = 18;

int n, m;
vector<int> g[MAXN];
int deg[MAXN];

int depth_arr[MAXN];
int up[MAXN][LOG];
long long prefix_sum[MAXN];  // 根到当前点路径上的点权和（点权 = 度数）

void init_graph(int n) {
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        deg[i] = 0;
        depth_arr[i] = 0;
        prefix_sum[i] = 0;
        for (int j = 0; j < LOG; j++) {
            up[i][j] = 0;
        }
    }
}

void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
    deg[u]++;
    deg[v]++;
}

void build_lca(int root) {
    vector<int> st;
    st.push_back(root);
    up[root][0] = 0;
    depth_arr[root] = 0;
    prefix_sum[root] = deg[root];

    while (!st.empty()) {
        int u = st.back();
        st.pop_back();

        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (v == up[u][0]) {
                continue;
            }

            up[v][0] = u;
            depth_arr[v] = depth_arr[u] + 1;
            prefix_sum[v] = prefix_sum[u] + deg[v];

            for (int j = 1; j < LOG; j++) {
                up[v][j] = up[up[v][j - 1]][j - 1];
            }

            st.push_back(v);
        }
    }
}

int kth_ancestor(int u, int k) {
    for (int j = 0; j < LOG; j++) {
        if (k & (1 << j)) {
            u = up[u][j];
        }
    }
    return u;
}

int lca(int a, int b) {
    if (depth_arr[a] < depth_arr[b]) {
        swap(a, b);
    }

    a = kth_ancestor(a, depth_arr[a] - depth_arr[b]);
    if (a == b) {
        return a;
    }

    for (int j = LOG - 1; j >= 0; j--) {
        if (up[a][j] != up[b][j]) {
            a = up[a][j];
            b = up[b][j];
        }
    }

    return up[a][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    init_graph(n);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }

    build_lca(1);

    while (m--) {
        int u, v;
        cin >> u >> v;

        int p = lca(u, v);
        long long ans = prefix_sum[u] + prefix_sum[v] - 2LL * prefix_sum[p] + deg[p];
        cout << ans << '\n';
    }

    return 0;
}
