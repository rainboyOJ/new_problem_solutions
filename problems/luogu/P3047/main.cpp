#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;
const int MAXK = 20 + 5;

int n, k_limit;
vector<int> g[MAXN];
int cows[MAXN];
int parent_arr[MAXN];
long long down_dp[MAXN][MAXK];
long long all_dp[MAXN][MAXK];
long long answer_arr[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k_limit;
    for (int i = 1; i <= n; i++) {
        g[i].clear();
        parent_arr[i] = 0;
        answer_arr[i] = 0;
        for (int d = 0; d <= k_limit; d++) {
            down_dp[i][d] = 0;
            all_dp[i][d] = 0;
        }
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for (int i = 1; i <= n; i++) {
        cin >> cows[i];
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

    // down_dp[u][d]：只看 u 子树时，和 u 距离恰好为 d 的牛数。
    for (int idx = (int)order.size() - 1; idx >= 0; idx--) {
        int u = order[idx];
        down_dp[u][0] = cows[u];
        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (v == parent_arr[u]) {
                continue;
            }
            for (int d = 1; d <= k_limit; d++) {
                down_dp[u][d] += down_dp[v][d - 1];
            }
        }
    }

    // all_dp[u][d]：整棵树里，和 u 距离恰好为 d 的牛数。
    for (int d = 0; d <= k_limit; d++) {
        all_dp[1][d] = down_dp[1][d];
    }

    for (size_t idx = 0; idx < order.size(); idx++) {
        int u = order[idx];
        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i];
            if (v == parent_arr[u]) {
                continue;
            }

            all_dp[v][0] = cows[v];
            for (int d = 1; d <= k_limit; d++) {
                // 先拿到“离 u 恰好 d-1”的所有牛，再减去来自 v 子树那部分，
                // 剩下的就是通过父亲方向贡献给 v 的牛数。
                long long from_parent_side = all_dp[u][d - 1];
                if (d >= 2) {
                    from_parent_side -= down_dp[v][d - 2];
                }
                all_dp[v][d] = down_dp[v][d] + from_parent_side;
            }
        }
    }

    for (int u = 1; u <= n; u++) {
        long long sum = 0;
        for (int d = 0; d <= k_limit; d++) {
            sum += all_dp[u][d];
        }
        answer_arr[u] = sum;
        cout << answer_arr[u] << '\n';
    }

    return 0;
}
