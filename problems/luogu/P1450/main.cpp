#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int coin[5];
int query_count;
vector<i64> dp;

i64 ways_with_unlimited(int s) {
    if (s < 0) {
        return 0;
    }
    return dp[s];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> coin[1] >> coin[2] >> coin[3] >> coin[4] >> query_count;

    vector<array<int, 5>> limits(query_count + 1);
    vector<int> target(query_count + 1);
    int max_s = 0;

    for (int i = 1; i <= query_count; i++) {
        cin >> limits[i][1] >> limits[i][2] >> limits[i][3] >> limits[i][4] >> target[i];
        max_s = max(max_s, target[i]);
    }

    // 先预处理“每种硬币都无限使用”时，凑出每个金额的方案数。
    dp.assign(max_s + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= 4; i++) {
        for (int s = coin[i]; s <= max_s; s++) {
            dp[s] += dp[s - coin[i]];
        }
    }

    for (int i = 1; i <= query_count; i++) {
        i64 ans = 0;

        // 容斥：mask 表示哪些硬币“超过了上界”。
        for (int mask = 0; mask < (1 << 4); mask++) {
            int need = target[i];
            int bits = 0;

            for (int j = 0; j < 4; j++) {
                if ((mask >> j) & 1) {
                    bits++;
                    need -= (limits[i][j + 1] + 1) * coin[j + 1];
                }
            }

            i64 add = ways_with_unlimited(need);
            if (bits & 1) {
                ans -= add;
            }
            else {
                ans += add;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
