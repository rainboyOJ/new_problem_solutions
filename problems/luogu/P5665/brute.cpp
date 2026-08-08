// brute.cpp：小数据动态规划，枚举最后一段起点，要求段和非递减。
#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 62);

int n, type_id_input;
long long a[105], prefix_sum[105];
long long dp[105][105]; // dp[i][j]：前 i 个数，最后一段从 j+1 到 i

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> type_id_input;
    if (type_id_input == 0) {
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
    } else {
        // 对拍生成器只生成 type=0。这里保留读取入口，避免格式不完整。
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + a[i];
    }

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = INF;
        }
    }

    for (int i = 1; i <= n; i++) {
        long long sum = prefix_sum[i];
        dp[i][0] = sum * sum;
    }

    for (int i = 1; i <= n; i++) {
        for (int last = 1; last < i; last++) {
            long long last_sum = prefix_sum[i] - prefix_sum[last];
            for (int prev = 0; prev < last; prev++) {
                if (dp[last][prev] == INF) {
                    continue;
                }
                long long prev_sum = prefix_sum[last] - prefix_sum[prev];
                if (prev_sum <= last_sum) {
                    dp[i][last] = min(dp[i][last], dp[last][prev] + last_sum * last_sum);
                }
            }
        }
    }

    long long answer = INF;
    for (int j = 0; j < n; j++) {
        answer = min(answer, dp[n][j]);
    }
    cout << answer << '\n';
    return 0;
}
