#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int s, n, m;
    cin >> s >> n >> m;

    vector<vector<int>> a(n + 1, vector<int>(s + 1));
    for (int i = 1; i <= s; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> a[j][i];
        }
    }

    for (int i = 1; i <= n; ++i) {
        sort(a[i].begin() + 1, a[i].end());
    }

    vector<int> dp(m + 1, 0);

    for (int castle = 1; castle <= n; ++castle) {
        vector<pair<int, int>> options;
        int beaten = 0;
        for (int k = 1; k <= s; ) {
            int v = a[castle][k];
            while (k <= s && a[castle][k] == v) {
                ++k;
                ++beaten;
            }
            int cost = 2 * v + 1;
            if (cost <= m) {
                options.push_back({cost, castle * beaten});
            }
        }

        vector<int> ndp = dp;
        for (auto [cost, value] : options) {
            for (int money = cost; money <= m; ++money) {
                ndp[money] = max(ndp[money], dp[money - cost] + value);
            }
        }
        dp.swap(ndp);
    }

    cout << dp[m] << '\n';
    return 0;
}
