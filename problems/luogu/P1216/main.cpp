#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
int a[MAXN][MAXN];
int dp[MAXN][MAXN]; // dp[i][j]：走到第 i 行第 j 个数时的最大和

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cin >> a[i][j];
        }
    }

    dp[1][1] = a[1][1];
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + a[i][j];
        }
    }

    int ans = 0;
    for (int j = 1; j <= n; j++) {
        ans = max(ans, dp[n][j]);
    }

    cout << ans << '\n';
    return 0;
}
