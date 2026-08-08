#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;
const int INF = 1e9;

int n;
int cost_days[MAXN][MAXN];
int dp[MAXN]; // dp[i]：从 1 号站到 i 号站的最少租金

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            cin >> cost_days[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
    }
    dp[1] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            dp[j] = min(dp[j], dp[i] + cost_days[i][j]);
        }
    }

    cout << dp[n] << '\n';
    return 0;
}
