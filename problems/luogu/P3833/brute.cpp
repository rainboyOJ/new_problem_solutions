// brute.cpp：真的把路径上的点都加上 d，再暴力统计子树和。
// 复杂度较高，只适合小数据理解和对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
vector<int> g[MAXN];
int parent_arr[MAXN];
int depth_arr[MAXN];
long long val[MAXN];

void build_parent_depth() {
    vector<int> st;
    st.push_back(0);
    parent_arr[0] = 0;
    depth_arr[0] = 0;

    while (!st.empty()) {
        int u = st.back();
        st.pop_back();

        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (v == parent_arr[u]) {
                continue;
            }
            parent_arr[v] = u;
            depth_arr[v] = depth_arr[u] + 1;
            st.push_back(v);
        }
    }
}

int lca(int a, int b) {
    while (depth_arr[a] > depth_arr[b]) {
        a = parent_arr[a];
    }
    while (depth_arr[b] > depth_arr[a]) {
        b = parent_arr[b];
    }
    while (a != b) {
        a = parent_arr[a];
        b = parent_arr[b];
    }
    return a;
}

void add_path(int u, int v, long long d) {
    int p = lca(u, v);

    while (u != p) {
        val[u] += d;
        u = parent_arr[u];
    }
    while (v != p) {
        val[v] += d;
        v = parent_arr[v];
    }
    val[p] += d;
}

long long dfs_sum(int u, int fa) {
    long long res = val[u];
    for (size_t i = 0; i < g[u].size(); i++) {
        int v = g[u][i];
        if (v == fa) {
            continue;
        }
        res += dfs_sum(v, u);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        g[i].clear();
        parent_arr[i] = 0;
        depth_arr[i] = 0;
        val[i] = 0;
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    build_parent_depth();

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
            cout << dfs_sum(u, parent_arr[u]) << '\n';
        }
    }

    return 0;
}
