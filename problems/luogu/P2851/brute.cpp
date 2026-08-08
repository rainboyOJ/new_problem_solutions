#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int n, target_sum;
int value_input[105], count_input[105];
vector<int> pay_dp, next_dp, change_dp;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> target_sum;
    for (int i = 1; i <= n; i++) {
        cin >> value_input[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> count_input[i];
    }

    int total_sum = 0;
    for (int i = 1; i <= n; i++) {
        total_sum += value_input[i] * count_input[i];
    }

    pay_dp.assign(total_sum + 1, INF);
    next_dp.assign(total_sum + 1, INF);
    pay_dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int s = 0; s <= total_sum; s++) {
            next_dp[s] = pay_dp[s];
        }

        for (int s = 0; s <= total_sum; s++) {
            if (pay_dp[s] >= INF) {
                continue;
            }

            // 直接枚举当前面值拿几枚，是最直白的小数据写法。
            for (int k = 1; k <= count_input[i]; k++) {
                int ns = s + k * value_input[i];
                if (ns > total_sum) {
                    break;
                }
                next_dp[ns] = min(next_dp[ns], pay_dp[s] + k);
            }
        }

        pay_dp.swap(next_dp);
    }

    change_dp.assign(total_sum + 1, INF);
    change_dp[0] = 0;
    for (int i = 1; i <= n; i++) {
        int v = value_input[i];
        for (int s = v; s <= total_sum; s++) {
            change_dp[s] = min(change_dp[s], change_dp[s - v] + 1);
        }
    }

    int answer = INF;
    for (int pay = target_sum; pay <= total_sum; pay++) {
        if (pay_dp[pay] >= INF || change_dp[pay - target_sum] >= INF) {
            continue;
        }
        answer = min(answer, pay_dp[pay] + change_dp[pay - target_sum]);
    }

    if (answer >= INF) {
        cout << -1 << '\n';
    }
    else {
        cout << answer << '\n';
    }

    return 0;
}
