#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int n, m, k;
int pack_mask[105];
int dp[1 << 20];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 1; i <= n; i++) {
        int mask = 0;
        for (int j = 1; j <= k; j++) {
            int x;
            cin >> x;
            mask |= 1 << (x - 1);
        }
        pack_mask[i] = mask;
    }

    int full = (1 << m) - 1;
    for (int i = 0; i <= full; i++) {
        dp[i] = INF;
    }
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int mask = full; mask >= 0; mask--) {
            int nxt = mask | pack_mask[i];
            dp[nxt] = min(dp[nxt], dp[mask] + 1);
        }
    }

    if (dp[full] >= INF) {
        cout << -1 << '\n';
    } else {
        cout << dp[full] << '\n';
    }
    return 0;
}
