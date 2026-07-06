#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int NEG_INF = -1000000000;

int n;
long long a[MAXN];
long long pre[MAXN];
int dp[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = pre[i - 1] + a[i];
    }

    for (int i = 0; i <= n; i++) {
        dp[i] = NEG_INF;
    }
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < i; j++) {
            // 前 j 头牛必须已经能合法划分，才可以接上最后一组。
            if (dp[j] == NEG_INF) {
                continue;
            }
            // 如果区间 [j+1, i] 的和非负，那么它可以作为最后一组。
            if (pre[i] - pre[j] >= 0) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    if (dp[n] == NEG_INF) {
        cout << "Impossible\n";
    } else {
        cout << dp[n] << '\n';
    }
    return 0;
}
