#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

int v, p;
int x[35];
int cost[35][35];
int dp[35][35];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> v >> p;
    for (int i = 1; i <= v; i++) {
        cin >> x[i];
    }
    sort(x + 1, x + v + 1);

    for (int l = 1; l <= v; l++) {
        for (int r = l; r <= v; r++) {
            int mid = (l + r) >> 1;
            for (int i = l; i <= r; i++) {
                cost[l][r] += abs(x[i] - x[mid]);
            }
        }
    }

    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    for (int k = 1; k <= p; k++) {
        for (int i = 1; i <= v; i++) {
            for (int j = 0; j < i; j++) {
                dp[k][i] = min(dp[k][i], dp[k - 1][j] + cost[j + 1][i]);
            }
        }
    }

    cout << dp[p][v] << '\n';
    return 0;
}
