/**
 * Problem: luogu P1052 - [NOIP 2005 提高组] 过河 (Brute Force)
 * Author: rainboy
 * Date: 2026-11-11 00:15
 * Description: 小规模无压缩纯线性 DP 基准实现
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAX_LEN = 20005;

int L, S, T, M;
bool stone[MAX_LEN];
int dp[MAX_LEN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> L >> S >> T >> M)) return 0;
    for (int i = 1; i <= M; ++i) {
        int pos;
        cin >> pos;
        if (pos <= L) {
            stone[pos] = true;
        }
    }

    if (S == T) {
        int ans = 0;
        for (int i = S; i <= L; i += S) {
            if (stone[i]) ans++;
        }
        cout << ans << "\n";
        return 0;
    }

    for (int i = 1; i <= L + T; ++i) {
        dp[i] = INF;
    }
    dp[0] = 0;

    for (int i = 1; i <= L + T; ++i) {
        for (int j = S; j <= T; ++j) {
            if (i >= j && dp[i - j] != INF) {
                dp[i] = min(dp[i], dp[i - j] + (stone[i] ? 1 : 0));
            }
        }
    }

    int ans = INF;
    for (int i = L; i < L + T; ++i) {
        ans = min(ans, dp[i]);
    }

    cout << ans << "\n";

    return 0;
}
