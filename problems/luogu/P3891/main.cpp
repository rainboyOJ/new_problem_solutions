#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXT = 1005;
const long long NEG_INF = -(1LL << 60);

int n, m, target;
int a[MAXN];
long long b[MAXN];
long long gain[MAXT]; // gain[c] 表示花费 c 资源，当秒最多新增多少采集效率
long long dp[MAXT], ndp[MAXT];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> target;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i];
    }

    if (m >= target) {
        cout << 0 << '\n';
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        if (a[i] == 0 && b[i] > 0) {
            // 0 代价且正收益的单位可以无限造，1 秒内必达目标。
            cout << 1 << '\n';
            return 0;
        }
    }

    for (int i = 0; i <= target; i++) {
        gain[i] = NEG_INF;
    }
    gain[0] = 0;

    // 完全背包：预处理“花费 c 资源最多能新增多少采集效率”。
    for (int i = 1; i <= n; i++) {
        if (a[i] <= 0 || a[i] > target || b[i] <= 0) {
            continue;
        }
        for (int cost = a[i]; cost <= target; cost++) {
            if (gain[cost - a[i]] == NEG_INF) {
                continue;
            }
            gain[cost] = max(gain[cost], gain[cost - a[i]] + b[i]);
        }
    }

    for (int i = 0; i < target; i++) {
        dp[i] = NEG_INF;
    }
    dp[m] = 0; // 第 0 秒结束时，手里有 m 资源，已有采集效率为 0

    for (int day = 0; day <= target; day++) {
        for (int i = 0; i < target; i++) {
            ndp[i] = NEG_INF;
        }

        for (int res = 0; res < target; res++) {
            if (dp[res] == NEG_INF) {
                continue;
            }

            long long prod = dp[res];

            for (int cost = 0; cost <= res; cost++) {
                if (gain[cost] == NEG_INF) {
                    continue;
                }

                long long add = gain[cost];
                long long next_prod = prod + add;
                if (next_prod > target) {
                    next_prod = target;
                }

                long long next_res = 1LL * res - cost + prod + add;
                if (next_res >= target) {
                    cout << day + 1 << '\n';
                    return 0;
                }

                if (next_prod > ndp[next_res]) {
                    ndp[next_res] = next_prod;
                }
            }
        }

        for (int i = 0; i < target; i++) {
            dp[i] = ndp[i];
        }
    }

    return 0;
}
