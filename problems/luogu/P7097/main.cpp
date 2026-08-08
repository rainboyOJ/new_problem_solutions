#include <bits/stdc++.h>
using namespace std;

const int MAXP = 205;
const long long NEG_INF = -(1LL << 60);

int subtask_id;
int n, m, w;
long long k[MAXP * 500];
int p[MAXP * 500];
long long best_k[MAXP];
long long dp[2][205];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> subtask_id;
    cin >> n >> m >> w;
    for (int i = 1; i <= m; i++) {
        cin >> k[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> p[i];
    }

    long long xa, xb;
    int da, db;
    cin >> xa >> xb >> da >> db;

    for (int i = 0; i < MAXP; i++) {
        best_k[i] = NEG_INF;
    }
    best_k[0] = 0;

    // 只需要关心总 p 不超过 200 的方案。
    for (int i = 1; i <= m; i++) {
        if (p[i] > 200) {
            continue;
        }
        for (int s = 200; s >= p[i]; s--) {
            if (best_k[s - p[i]] == NEG_INF) {
                continue;
            }
            best_k[s] = max(best_k[s], best_k[s - p[i]] + k[i]);
        }
    }

    long long unit_a = xa / 100000;
    long long unit_b = xb / 100000;
    int offset = 100;

    for (int d = -100; d <= 100; d++) {
        dp[0][d + offset] = 0;
    }

    for (int turn = 1; turn <= n; turn++) {
        int cur = turn & 1;
        int pre = cur ^ 1;

        for (int d = -100; d <= 100; d++) {
            if (d <= 0) {
                // 轮到扶苏行动，他希望最大化最终伤害差。
                long long best = NEG_INF;
                int max_sum_p = 100 - d - w;
                if (max_sum_p < 0) {
                    dp[cur][d + offset] = NEG_INF;
                    continue;
                }
                if (max_sum_p > 200) {
                    max_sum_p = 200;
                }

                for (int sum_p = 0; sum_p <= max_sum_p; sum_p++) {
                    if (best_k[sum_p] == NEG_INF) {
                        continue;
                    }
                    int next_d = d + w + sum_p;
                    long long damage = xa + unit_a * best_k[sum_p];
                    best = max(best, damage + dp[pre][next_d + offset]);
                }
                dp[cur][d + offset] = best;
            } else {
                // 轮到扶咕咕行动，她会最小化扶苏 - 扶咕咕的伤害差。
                long long best = NEG_INF;
                int max_sum_p = d + 100 - w;
                if (max_sum_p < 0) {
                    dp[cur][d + offset] = NEG_INF;
                    continue;
                }
                if (max_sum_p > 200) {
                    max_sum_p = 200;
                }

                for (int sum_p = 0; sum_p <= max_sum_p; sum_p++) {
                    if (best_k[sum_p] == NEG_INF) {
                        continue;
                    }
                    int next_d = d - w - sum_p;
                    long long damage = xb + unit_b * best_k[sum_p];
                    best = max(best, damage - dp[pre][next_d + offset]);
                }
                dp[cur][d + offset] = -best;
            }
        }
    }

    cout << dp[n & 1][da - db + offset] << '\n';
    return 0;
}
