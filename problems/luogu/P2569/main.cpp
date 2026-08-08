#include <bits/stdc++.h>
using namespace std;

const int MAXT = 2005;
const int MAXP = 2005;
const long long NEG_INF = -(1LL << 60);

int T, MaxP, W;
int ap[MAXT], bp[MAXT], as[MAXT], bs[MAXT];
// dp[day][hold]：到第 day 天结束时，手里持有 hold 股股票的最大净收益。
long long dp[MAXT][MAXP];
// 单调队列里存的是候选持股数下标。
int q[MAXP];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T >> MaxP >> W;
    for (int i = 1; i <= T; i++) {
        cin >> ap[i] >> bp[i] >> as[i] >> bs[i];
    }

    for (int i = 0; i <= T; i++) {
        for (int j = 0; j <= MaxP; j++) {
            dp[i][j] = NEG_INF;
        }
    }
    dp[0][0] = 0;

    for (int day = 1; day <= T; day++) {
        // 今天什么都不做，直接继承昨天的状态。
        for (int hold = 0; hold <= MaxP; hold++) {
            dp[day][hold] = dp[day - 1][hold];
        }

        // 如果今天发生交易，那么上一次交易最晚只能在 pre 这一天或更早。
        // 更早的状态已经通过“什么都不做”的转移传到了 dp[pre][*] 里。
        int pre = day - W - 1;
        if (pre < 0) {
            pre = 0;
        }

        // 买入转移：
        // dp[day][hold] = max(dp[pre][k] - (hold-k)*ap[day])
        // = -hold*ap[day] + max(dp[pre][k] + k*ap[day])
        int head = 0, tail = -1;
        for (int hold = 0; hold <= MaxP; hold++) {
            while (head <= tail && q[head] < hold - as[day]) {
                head++;
            }

            long long cur_value = dp[pre][hold] + 1LL * hold * ap[day];
            while (head <= tail) {
                int last = q[tail];
                long long last_value = dp[pre][last] + 1LL * last * ap[day];
                if (last_value <= cur_value) {
                    tail--;
                } else {
                    break;
                }
            }
            q[++tail] = hold;

            int best = q[head];
            dp[day][hold] = max(dp[day][hold],
                                dp[pre][best] - 1LL * (hold - best) * ap[day]);
        }

        // 卖出转移：
        // dp[day][hold] = max(dp[pre][k] + (k-hold)*bp[day])
        // = -hold*bp[day] + max(dp[pre][k] + k*bp[day])
        head = 0;
        tail = -1;
        for (int hold = MaxP; hold >= 0; hold--) {
            while (head <= tail && q[head] > hold + bs[day]) {
                head++;
            }

            long long cur_value = dp[pre][hold] + 1LL * hold * bp[day];
            while (head <= tail) {
                int last = q[tail];
                long long last_value = dp[pre][last] + 1LL * last * bp[day];
                if (last_value <= cur_value) {
                    tail--;
                } else {
                    break;
                }
            }
            q[++tail] = hold;

            int best = q[head];
            dp[day][hold] = max(dp[day][hold],
                                dp[pre][best] + 1LL * (best - hold) * bp[day]);
        }
    }

    // 枚举最后一天结束时的持股数，取最大净收益。
    long long ans = 0;
    for (int hold = 0; hold <= MaxP; hold++) {
        ans = max(ans, dp[T][hold]);
    }

    cout << ans << '\n';
    return 0;
}
