#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int N;
ll M;
int K[105], C[105];       // K[i] 上限展示量, C[i] 皮肤单价

// 乘法防溢出，超过 limit 就截断为 limit。
ll clamp_mul(ll a, int b, ll limit) {
    __int128 v = (__int128)a * b;
    if (v > limit) return limit;
    return (ll)v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for (int i = 0; i < N; i++) cin >> K[i];
    for (int i = 0; i < N; i++) cin >> C[i];

    int limit = 0;
    for (int i = 0; i < N; i++) {
        limit += K[i] * C[i];            // 花费的上限
    }

    // dp[cost] 表示花费 cost 元能达到的最大展示数量。
    vector<ll> dp(limit + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < N; i++) {
        vector<ll> ndp = dp;
        for (int cost = 0; cost <= limit; cost++) {
            if (dp[cost] == 0) continue;
            // 在当前英雄上买 x 份皮肤（x ≥ 2）
            for (int x = 2; x <= K[i]; x++) {
                int nc = cost + x * C[i];
                if (nc > limit) break;
                ndp[nc] = max(ndp[nc], clamp_mul(dp[cost], x, M));
            }
        }
        dp.swap(ndp);
    }

    // 找到最小的花费使展示数量 ≥ M。
    for (int cost = 0; cost <= limit; cost++) {
        if (dp[cost] >= M) {
            cout << cost << '\n';
            return 0;
        }
    }
    return 0;
}
