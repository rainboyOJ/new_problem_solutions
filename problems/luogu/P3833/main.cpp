#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
const int LOG = 18;

struct Fenwick {
    int n;
    long long bit[MAXN];

    void init(int n_) {
        n = n_;
        for (int i = 1; i <= n; i++) {
            bit[i] = 0;
        }
    }

    void add(int x, long long delta) {
        for (int i = x; i <= n; i += i & -i) {
            bit[i] += delta;
        }
    }

    long long sum_prefix(int x) const {
        long long res = 0;
        for (int i = x; i > 0; i -= i & -i) {
            res += bit[i];
        }
        return res;
    }

    long long range_sum(int l, int r) const {
        if (l > r) {
            return 0;
        }
        return sum_prefix(r) - sum_prefix(l - 1);
    }
};

int n;
vector<int> g[MAXN];
int parent_arr[MAXN];
int depth_arr[MAXN];
int up[MAXN][LOG];
int tin[MAXN], tout[MAXN], dfs_clock;
int iter_idx[MAXN];

Fenwick bit_cnt;   // 维护树上差分值 diff
Fenwick bit_depth; // 维护 diff * (depth + 1)

void init_tree(int n) {
    dfs_clock = 0;
    for (int i = 0; i < n; i++) {
        g[i].clear();
        parent_arr[i] = 0;
        depth_arr[i] = 0;
        tin[i] = 0;
        tout[i] = 0;
        iter_idx[i] = 0;
        for (int j = 0; j < LOG; j++) {
            up[i][j] = 0;
        }
    }
}

void add_edge(int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

void build_lca_and_dfn() {
    vector<int> st;
    st.push_back(0);
    parent_arr[0] = 0;
    depth_arr[0] = 0;
    tin[0] = ++dfs_clock;

    while (!st.empty()) {
        int u = st.back();

        if (iter_idx[u] < (int)g[u].size()) {
            int v = g[u][iter_idx[u]++];
            if (v == parent_arr[u]) {
                continue;
            }

            parent_arr[v] = u;
            depth_arr[v] = depth_arr[u] + 1;
            up[v][0] = u;
            for (int j = 1; j < LOG; j++) {
                up[v][j] = up[up[v][j - 1]][j - 1];
            }

            tin[v] = ++dfs_clock;
            st.push_back(v);
        }
        else {
            tout[u] = dfs_clock;
            st.pop_back();
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

void add_diff(int u, long long delta) {
    int pos = tin[u];
    bit_cnt.add(pos, delta);
    bit_depth.add(pos, delta * (depth_arr[u] + 1LL));
}

// 对路径 u-v 上所有点加 d。
// 使用树上差分：diff[u] += d, diff[v] += d, diff[lca] -= d, diff[parent(lca)] -= d。
void add_path(int u, int v, long long d) {
    int p = lca(u, v);

    add_diff(u, d);
    add_diff(v, d);
    add_diff(p, -d);
    if (p != 0) {
        add_diff(parent_arr[p], -d);
    }
}

// 当前子树和：
// sum_{x in subtree(u)} value[x]
// = sum_{y in subtree(u)} diff[y] * (depth[y] - depth[u] + 1)
// = sum(diff * (depth+1)) - depth[u] * sum(diff)
long long query_subtree(int u) {
    long long s1 = bit_cnt.range_sum(tin[u], tout[u]);
    long long s2 = bit_depth.range_sum(tin[u], tout[u]);
    return s2 - 1LL * depth_arr[u] * s1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    init_tree(n);

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        add_edge(u, v);
    }

    build_lca_and_dfn();
    bit_cnt.init(n);
    bit_depth.init(n);

    int q;
    cin >> q;
    while (q--) {
        char op;
        cin >> op;

        if (op == 'A') {
            int u, v;
            long long d;
            cin >> u >> v >> d;
            add_path(u, v, d);
        }
        else {
            int u;
            cin >> u;
            cout << query_subtree(u) << '\n';
        }
    }

    return 0;
}
