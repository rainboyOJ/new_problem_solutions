/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 20:58
 * update_at: 2026-10-01 20:58
 */
// brute.cpp：小数据暴力解，枚举最后一段起点，要求段和非递减。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = (1LL << 62);

int n, type_id_input;
ll a[105], prefix_sum[105];
// dp[i][j]：前 i 个数划分完毕，最后一段为 (j+1)..i 时的最小代价。
// 要求最后一段的段和不小于前一段的段和。
ll dp[105][105];

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

    // 第一段直接从 1 开始。
    for (int i = 1; i <= n; i++) {
        ll sum = prefix_sum[i];
        dp[i][0] = sum * sum;
    }

    // 枚举最后一段的起点 last，以及上一段的结尾 prev。
    for (int i = 1; i <= n; i++) {
        for (int last = 1; last < i; last++) {
            ll last_sum = prefix_sum[i] - prefix_sum[last];
            for (int prev = 0; prev < last; prev++) {
                if (dp[last][prev] == INF) {
                    continue;
                }
                ll prev_sum = prefix_sum[last] - prefix_sum[prev];
                if (prev_sum <= last_sum) {
                    dp[i][last] = min(dp[i][last], dp[last][prev] + last_sum * last_sum);
                }
            }
        }
    }

    ll answer = INF;
    for (int j = 0; j < n; j++) {
        answer = min(answer, dp[n][j]);
    }
    cout << answer << '\n';
    return 0;
}
