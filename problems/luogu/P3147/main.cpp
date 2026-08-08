#include <bits/stdc++.h>
using namespace std;

const int MAXN = 262144 + 5;
const int MAXV = 65;

static int a[MAXN];
static int dp[MAXN][MAXV];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        dp[i][a[i]] = i;
        ans = max(ans, a[i]);
    }

    // dp[i][v] 表示从位置 i 开始，最短到哪里能合成一个值为 v 的数。
    for (int v = 2; v < MAXV; ++v) {
        for (int i = 1; i <= n; ++i) {
            if (dp[i][v - 1] == 0) {
                continue;
            }
            int mid = dp[i][v - 1];
            if (mid + 1 > n || dp[mid + 1][v - 1] == 0) {
                continue;
            }
            dp[i][v] = dp[mid + 1][v - 1];
            ans = max(ans, v);
        }
    }

    cout << ans << '\n';
    return 0;
}
