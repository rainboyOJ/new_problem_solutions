#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int NEG_INF = -1000000000;

int n, m;
string a, b;
int score[5][5] = {
    {5, -1, -2, -1, -3},
    {-1, 5, -3, -2, -4},
    {-2, -3, 5, -2, -2},
    {-1, -2, -2, 5, -1},
    {-3, -4, -2, -1, 0}
};
int dp[MAXN][MAXN];

int id(char ch) {
    if (ch == 'A') return 0;
    if (ch == 'C') return 1;
    if (ch == 'G') return 2;
    if (ch == 'T') return 3;
    return 4;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> a;
    cin >> m >> b;

    a = " " + a;
    b = " " + b;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            dp[i][j] = NEG_INF;
        }
    }

    dp[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        dp[i][0] = dp[i - 1][0] + score[id(a[i])][4];
    }
    for (int j = 1; j <= m; j++) {
        dp[0][j] = dp[0][j - 1] + score[4][id(b[j])];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            // 1. a[i] 和 b[j] 对齐
            dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + score[id(a[i])][id(b[j])]);

            // 2. a[i] 和 '-' 对齐
            dp[i][j] = max(dp[i][j], dp[i - 1][j] + score[id(a[i])][4]);

            // 3. '-' 和 b[j] 对齐
            dp[i][j] = max(dp[i][j], dp[i][j - 1] + score[4][id(b[j])]);
        }
    }

    cout << dp[n][m] << '\n';
    return 0;
}
