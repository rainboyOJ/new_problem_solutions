#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

struct Edge {
    int to;
    int w;
};

int n, q_need;
vector<Edge> g[MAXN];
int parent_arr[MAXN];
int parent_w[MAXN];
int sub_edge_cnt[MAXN];
int dp[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q_need;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        parent_arr[i] = 0;
        parent_w[i] = 0;
        sub_edge_cnt[i] = 0;
        for (int j = 0; j <= q_need; j++) {
            dp[i][j] = 0;
        }
    }

    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    vector<int> order;
    order.reserve(n);
    stack<int> st;
    st.push(1);
    parent_arr[1] = 0;

    while (!st.empty()) {
        int u = st.top();
        st.pop();
        order.push_back(u);
        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i].to;
            if (v == parent_arr[u]) {
                continue;
            }
            parent_arr[v] = u;
            parent_w[v] = g[u][i].w;
            st.push(v);
        }
    }

    for (int idx = (int)order.size() - 1; idx >= 0; idx--) {
        int u = order[idx];
        sub_edge_cnt[u] = 0;

        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i].to;
            int w = g[u][i].w;
            if (v == parent_arr[u]) {
                continue;
            }

            static int new_dp[MAXN];
            for (int t = 0; t <= q_need; t++) {
                new_dp[t] = dp[u][t];
            }

            for (int used = 0; used <= min(q_need, sub_edge_cnt[u]); used++) {
                for (int take = 0; take <= min(q_need - used - 1, sub_edge_cnt[v]); take++) {
                    // 若要从儿子子树里保留 take 条边，就必须先保留 u-v 这条边。
                    new_dp[used + take + 1] = max(new_dp[used + take + 1],
                                                   dp[u][used] + dp[v][take] + w);
                }
            }

            sub_edge_cnt[u] += sub_edge_cnt[v] + 1;
            for (int t = 0; t <= q_need; t++) {
                dp[u][t] = new_dp[t];
            }
        }
    }

    cout << dp[1][q_need] << '\n';
    return 0;
}
