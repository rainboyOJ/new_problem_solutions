#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
const int LOG = 18;

int n, q;
vector<int> child[MAXN];
int depth_arr[MAXN];
int up[MAXN][LOG];
int path_max_id[MAXN];

void init_tree(int n) {
    for (int i = 0; i < n; i++) {
        child[i].clear();
        depth_arr[i] = 0;
        path_max_id[i] = 0;
        for (int j = 0; j < LOG; j++) {
            up[i][j] = 0;
        }
    }
}

void build_lca() {
    vector<int> st;
    st.push_back(0);

    while (!st.empty()) {
        int u = st.back();
        st.pop_back();

        for (size_t i = 0; i < child[u].size(); i++) {
            int v = child[u][i];
            depth_arr[v] = depth_arr[u] + 1;
            up[v][0] = u;
            path_max_id[v] = max(path_max_id[u], v);

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

    cin >> n;
    init_tree(n);

    for (int i = 1; i < n; i++) {
        int f;
        cin >> f;
        child[f].push_back(i);
    }

    path_max_id[0] = 0;
    build_lca();

    cin >> q;
    while (q--) {
        int m;
        cin >> m;

        int cur_lca;
        cin >> cur_lca;

        for (int i = 2; i <= m; i++) {
            int x;
            cin >> x;
            cur_lca = lca(cur_lca, x);
        }

        // 能主持所有人的员工，等价于“所有参与者公共祖先”。
        // 在这些公共祖先里取编号最大值，就是根到 LCA 路径上的最大编号。
        cout << path_max_id[cur_lca] << '\n';
    }

    return 0;
}
