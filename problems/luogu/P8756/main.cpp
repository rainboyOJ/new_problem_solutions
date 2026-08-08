#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int MAXS = 1 << 6;

int n, m, k_need;
int bit_cnt[MAXS];
int ok1[MAXS][MAXS];
int ok2[MAXS][MAXS];
int valid_next[MAXS][MAXS][MAXS];
int valid_cnt[MAXS][MAXS];
int dp[2][MAXS][MAXS][25];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k_need;

    int full = 1 << n;
    for (int s = 0; s < full; s++) {
        bit_cnt[s] = __builtin_popcount((unsigned int) s);
    }

    int row_mask = full - 1;
    for (int a = 0; a < full; a++) {
        int attack_adj = ((a << 2) | (a >> 2)) & row_mask;
        int attack_far = ((a << 1) | (a >> 1)) & row_mask;
        for (int b = 0; b < full; b++) {
            ok1[a][b] = ((attack_adj & b) == 0);
            ok2[a][b] = ((attack_far & b) == 0);
        }
    }

    for (int p2 = 0; p2 < full; p2++) {
        for (int p1 = 0; p1 < full; p1++) {
            valid_cnt[p2][p1] = 0;
            for (int cur = 0; cur < full; cur++) {
                if (ok1[p1][cur] && ok2[p2][cur]) {
                    valid_next[p2][p1][valid_cnt[p2][p1]++] = cur;
                }
            }
        }
    }

    memset(dp, 0, sizeof(dp));
    dp[0][0][0][0] = 1;

    for (int col = 0; col < m; col++) {
        int now = col & 1;
        int nxt = now ^ 1;
        memset(dp[nxt], 0, sizeof(dp[nxt]));

        for (int p2 = 0; p2 < full; p2++) {
            for (int p1 = 0; p1 < full; p1++) {
                for (int used = 0; used <= k_need; used++) {
                    int ways = dp[now][p2][p1][used];
                    if (ways == 0) {
                        continue;
                    }
                    for (int idx = 0; idx < valid_cnt[p2][p1]; idx++) {
                        int cur = valid_next[p2][p1][idx];
                        int nused = used + bit_cnt[cur];
                        if (nused > k_need) {
                            continue;
                        }
                        int &ref = dp[nxt][p1][cur][nused];
                        ref += ways;
                        if (ref >= MOD) {
                            ref -= MOD;
                        }
                    }
                }
            }
        }
    }

    int last = m & 1;
    int ans = 0;
    for (int p2 = 0; p2 < full; p2++) {
        for (int p1 = 0; p1 < full; p1++) {
            ans += dp[last][p2][p1][k_need];
            if (ans >= MOD) {
                ans -= MOD;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
