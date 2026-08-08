#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXK = 25;
const int NEG_INF = -0x3f3f3f3f;

int n, k;
int a[MAXN];
int dp[MAXN][MAXK][3];

int win_score(int my_gesture, int opp_gesture) {
    if (my_gesture == 0 && opp_gesture == 2) {
        return 1; // H 胜 S
    }
    if (my_gesture == 1 && opp_gesture == 0) {
        return 1; // P 胜 H
    }
    if (my_gesture == 2 && opp_gesture == 1) {
        return 1; // S 胜 P
    }
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        char ch;
        cin >> ch;
        if (ch == 'H') {
            a[i] = 0;
        }
        else if (ch == 'P') {
            a[i] = 1;
        }
        else {
            a[i] = 2;
        }
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            for (int s = 0; s < 3; s++) {
                dp[i][j][s] = NEG_INF;
            }
        }
    }

    for (int s = 0; s < 3; s++) {
        dp[0][0][s] = 0;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            for (int s = 0; s < 3; s++) {
                // 这一轮保持当前手势。
                dp[i][j][s] = max(dp[i][j][s], dp[i - 1][j][s]);

                // 这一轮前从另外两种手势切换过来。
                if (j > 0) {
                    for (int pre = 0; pre < 3; pre++) {
                        if (pre == s) {
                            continue;
                        }
                        dp[i][j][s] = max(dp[i][j][s], dp[i - 1][j - 1][pre]);
                    }
                }

                dp[i][j][s] += win_score(s, a[i]);
            }
        }
    }

    int ans = 0;
    for (int j = 0; j <= k; j++) {
        for (int s = 0; s < 3; s++) {
            ans = max(ans, dp[n][j][s]);
        }
    }

    cout << ans << '\n';
    return 0;
}
