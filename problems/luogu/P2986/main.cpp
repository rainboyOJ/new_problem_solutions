#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

struct Edge {
    int to;
    int w;
};

int n;
long long cows[MAXN];
vector<Edge> g[MAXN];
int parent_arr[MAXN];
int parent_w[MAXN];
long long sub_cows[MAXN];
long long dist_sum[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> cows[i];
        g[i].clear();
        parent_arr[i] = 0;
        parent_w[i] = 0;
        sub_cows[i] = 0;
        dist_sum[i] = 0;
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

    long long total_cows = 0;
    for (int idx = (int)order.size() - 1; idx >= 0; idx--) {
        int u = order[idx];
        sub_cows[u] = cows[u];
        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i].to;
            int w = g[u][i].w;
            if (v == parent_arr[u]) {
                continue;
            }
            sub_cows[u] += sub_cows[v];
            dist_sum[u] += dist_sum[v] + sub_cows[v] * w;
        }
    }
    total_cows = sub_cows[1];

    // 换根：从 u 换到儿子 v，v 子树里的牛会整体更近 w，
    // 其余牛会整体更远 w。
    for (size_t idx = 0; idx < order.size(); idx++) {
        int u = order[idx];
        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i].to;
            int w = g[u][i].w;
            if (v == parent_arr[u]) {
                continue;
            }
            dist_sum[v] = dist_sum[u] + (total_cows - 2LL * sub_cows[v]) * w;
        }
    }

    long long ans = dist_sum[1];
    for (int i = 2; i <= n; i++) {
        ans = min(ans, dist_sum[i]);
    }

    cout << ans << '\n';
    return 0;
}
