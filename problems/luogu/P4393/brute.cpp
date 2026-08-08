#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int n;
int a[MAXN];
int mx[MAXN][MAXN];
long long dp[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mx[i][i] = a[i];
        dp[i][i] = 0;
    }

    for (int len = 2; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            mx[l][r] = max(mx[l][r - 1], a[r]);
            dp[l][r] = (1LL << 62);

            // 最后一次合并一定是把 [l, k] 和 [k+1, r] 两段合并。
            // 这一段的最终值一定是整个区间最大值 mx[l][r]。
            for (int k = l; k < r; k++) {
                long long current = dp[l][k] + dp[k + 1][r] + mx[l][r];
                if (current < dp[l][r]) {
                    dp[l][r] = current;
                }
            }
        }
    }

    cout << dp[1][n] << '\n';

    return 0;
}
