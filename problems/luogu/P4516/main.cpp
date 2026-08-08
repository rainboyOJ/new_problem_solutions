#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXK = 105;
const int MOD = 1000000007;

int n, k;
vector<int> g[MAXN];
int parent_node[MAXN];
int order_arr[MAXN];
int order_cnt;
int subtree_size[MAXN];
int f[MAXN][MAXK][2][2];
int tmp[MAXK][2][2];

void add_mod(int &x, long long y) {
    x = (x + y) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> st;
    st.push_back(1);
    parent_node[1] = 0;

    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        order_arr[++order_cnt] = u;
        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (v == parent_node[u]) {
                continue;
            }
            parent_node[v] = u;
            st.push_back(v);
        }
    }

    for (int idx = order_cnt; idx >= 1; idx--) {
        int u = order_arr[idx];

        subtree_size[u] = 1;
        f[u][0][0][0] = 1;
        if (k >= 1) {
            f[u][1][1][0] = 1;
        }

        for (size_t e = 0; e < g[u].size(); e++) {
            int v = g[u][e];
            if (v == parent_node[u]) {
                continue;
            }

            int limit_u = min(subtree_size[u], k);
            int limit_v = min(subtree_size[v], k);
            int limit_all = min(subtree_size[u] + subtree_size[v], k);

            for (int i = 0; i <= limit_all; i++) {
                for (int a = 0; a < 2; a++) {
                    for (int b = 0; b < 2; b++) {
                        tmp[i][a][b] = 0;
                    }
                }
            }

            for (int i = 0; i <= limit_u; i++) {
                for (int j = 0; j <= limit_v && i + j <= k; j++) {
                    for (int sel_u = 0; sel_u < 2; sel_u++) {
                        for (int cov_u = 0; cov_u < 2; cov_u++) {
                            int ways_u = f[u][i][sel_u][cov_u];
                            if (ways_u == 0) {
                                continue;
                            }
                            for (int sel_v = 0; sel_v < 2; sel_v++) {
                                for (int cov_v = 0; cov_v < 2; cov_v++) {
                                    int ways_v = f[v][j][sel_v][cov_v];
                                    if (ways_v == 0) {
                                        continue;
                                    }

                                    if ((cov_v | sel_u) == 0) {
                                        continue;
                                    }

                                    add_mod(
                                        tmp[i + j][sel_u][cov_u | sel_v],
                                        1LL * ways_u * ways_v
                                    );
                                }
                            }
                        }
                    }
                }
            }

            subtree_size[u] += subtree_size[v];
            if (subtree_size[u] > k) {
                subtree_size[u] = k;
            }

            for (int i = 0; i <= subtree_size[u]; i++) {
                for (int a = 0; a < 2; a++) {
                    for (int b = 0; b < 2; b++) {
                        f[u][i][a][b] = tmp[i][a][b];
                    }
                }
            }
        }
    }

    int answer = f[1][k][0][1];
    add_mod(answer, f[1][k][1][1]);
    cout << answer << '\n';
    return 0;
}
