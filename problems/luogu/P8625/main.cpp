#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

int n;
long long val[MAXN];
vector<int> g[MAXN];
int parent_arr[MAXN];
long long dp[MAXN];
long long ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> val[i];
        g[i].clear();
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
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
            int v = g[u][i];
            if (v == parent_arr[u]) {
                continue;
            }
            parent_arr[v] = u;
            st.push(v);
        }
    }

    ans = -(1LL << 60);
    for (int idx = (int)order.size() - 1; idx >= 0; idx--) {
        int u = order[idx];
        dp[u] = val[u];

        // 只有对子树贡献为正时，才值得把这棵子树连进来。
        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (v == parent_arr[u]) {
                continue;
            }
            if (dp[v] > 0) {
                dp[u] += dp[v];
            }
        }

        ans = max(ans, dp[u]);
    }

    if (ans < 0) {
        ans = 0;
    }
    cout << ans << '\n';
    return 0;
}
