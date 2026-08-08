#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int T;
int n;
int a[MAXN];
int dp[MAXN];        // dp[i]：以 i 结尾的最长不下降子序列长度
long long cnt[MAXN]; // cnt[i]：达到 dp[i] 的方案数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            dp[i] = 1;
            cnt[i] = 1;
        }

        int best_len = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j < i; j++) {
                if (a[j] <= a[i]) {
                    if (dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                        cnt[i] = cnt[j];
                    }
                    else if (dp[j] + 1 == dp[i]) {
                        cnt[i] += cnt[j];
                    }
                }
            }
            best_len = max(best_len, dp[i]);
        }

        long long ways = 0;
        for (int i = 1; i <= n; i++) {
            if (dp[i] == best_len) {
                ways += cnt[i];
            }
        }

        cout << best_len << ' ' << ways << '\n';
    }

    return 0;
}
