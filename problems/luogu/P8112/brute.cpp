#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int len_t, len_s;
    string t, s;
    cin >> len_t >> len_s;
    cin >> t >> s;

    int m = (int) t.size();
    int n = (int) s.size();

    vector<int> dp(n + 1, INF);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        if (dp[i] == INF) {
            continue;
        }
        for (int len = 1; len <= m && i + len <= n; len++) {
            bool same = true;
            for (int j = 0; j < len; j++) {
                if (s[i + j] != t[j]) {
                    same = false;
                    break;
                }
            }
            if (same) {
                dp[i + len] = min(dp[i + len], dp[i] + 1);
            }
        }
    }

    if (dp[n] == INF) {
        cout << "Fake\n";
    }
    else {
        cout << dp[n] << '\n';
    }
    return 0;
}
