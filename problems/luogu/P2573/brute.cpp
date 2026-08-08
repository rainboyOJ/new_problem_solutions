// brute.cpp：小数据集合 DP，直接按“已访问景点集合”转移。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 12;
const long long INF = (1LL << 60);

int n, m;
int h[MAXN];
vector<pair<int, int>> g[MAXN];
long long dp[1 << MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        g[i].clear();
    }

    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (h[u] >= h[v]) {
            g[u].push_back({v, w});
        }
        if (h[v] >= h[u]) {
            g[v].push_back({u, w});
        }
    }

    int max_mask = 1 << n;
    for (int i = 0; i < max_mask; i++) {
        dp[i] = INF;
    }
    dp[1 << 0] = 0;

    int best_cnt = 1;
    long long best_sum = 0;

    for (int mask = 0; mask < max_mask; mask++) {
        if (dp[mask] == INF) {
            continue;
        }

        int cnt = __builtin_popcount((unsigned)mask);
        if (cnt > best_cnt || (cnt == best_cnt && dp[mask] < best_sum)) {
            best_cnt = cnt;
            best_sum = dp[mask];
        }

        for (int u = 1; u <= n; u++) {
            if (((mask >> (u - 1)) & 1) == 0) {
                continue;
            }
            for (pair<int, int> e : g[u]) {
                int v = e.first;
                int w = e.second;
                if ((mask >> (v - 1)) & 1) {
                    continue;
                }
                int next_mask = mask | (1 << (v - 1));
                dp[next_mask] = min(dp[next_mask], dp[mask] + w);
            }
        }
    }

    cout << best_cnt << ' ' << best_sum << '\n';

    return 0;
}
