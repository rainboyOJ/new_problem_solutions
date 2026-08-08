#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

static int a[105];
static int dp[105][105];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int P, Q;
    cin >> P >> Q;
    a[0] = 0;
    for (int i = 1; i <= Q; ++i) {
        cin >> a[i];
    }
    a[Q + 1] = P + 1;

    for (int len = 2; len <= Q + 1; ++len) {
        for (int l = 0; l + len <= Q + 1; ++l) {
            int r = l + len;
            dp[l][r] = INF;
            for (int k = l + 1; k < r; ++k) {
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k][r] + a[r] - a[l] - 2);
            }
            if (dp[l][r] == INF) {
                dp[l][r] = 0;
            }
        }
    }

    cout << dp[0][Q + 1] << '\n';
    return 0;
}
