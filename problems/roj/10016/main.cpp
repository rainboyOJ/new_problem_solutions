#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
long long dp[MAXN][MAXN][2];
long long a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    if (!(cin >> n >> k)) return 0;
    
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    long long ans = 0;
    for (int i = 2; i < n; i++) {
        for (int j = 0; j <= k; j++) {
            if (a[i] < a[i-1] && a[i] < a[i+1]) {
                dp[i][j][1] = dp[i-1][j][0] + a[i];
                dp[i][j][0] = dp[i-1][j][1];
            } else {
                if (j > 0) {
                    dp[i][j][1] = dp[i-1][j-1][0] + min(a[i-1] - 1, a[i+1] - 1);
                }
                dp[i][j][0] = max(dp[i-1][j][0], dp[i-1][j][1]);
            }
            ans = max(ans, dp[i][j][0]);
            ans = max(ans, dp[i][j][1]);
        }
    }
    
    cout << ans << "\n";
    return 0;
}
