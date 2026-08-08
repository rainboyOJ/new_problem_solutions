#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
const long long MOD = 1000000007LL;

int n, k;
vector<int> g[MAXN];
int fixed_color[MAXN];
int parent_arr[MAXN];
long long dp[MAXN][4];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        fixed_color[i] = 0;
        for (int c = 1; c <= 3; c++) {
            dp[i][c] = 0;
        }
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 1; i <= k; i++) {
        int u, c;
        cin >> u >> c;
        fixed_color[u] = c;
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

    for (int idx = (int)order.size() - 1; idx >= 0; idx--) {
        int u = order[idx];

        for (int c = 1; c <= 3; c++) {
            if (fixed_color[u] != 0 && fixed_color[u] != c) {
                dp[u][c] = 0;
                continue;
            }

            long long ways = 1;
            for (size_t i = 0; i < g[u].size(); i++) {
                int v = g[u][i];
                if (v == parent_arr[u]) {
                    continue;
                }

                long long child_ways = 0;
                for (int cc = 1; cc <= 3; cc++) {
                    if (cc == c) {
                        continue;
                    }
                    child_ways = (child_ways + dp[v][cc]) % MOD;
                }
                ways = ways * child_ways % MOD;
            }
            dp[u][c] = ways;
        }
    }

    long long ans = (dp[1][1] + dp[1][2] + dp[1][3]) % MOD;
    cout << ans << '\n';
    return 0;
}
