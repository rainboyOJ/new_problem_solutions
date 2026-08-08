#include <bits/stdc++.h>
using namespace std;

const int MAXN = 6005;
const int MAXS = 30005;
const int INF = 1e9;

int n;
int t1[MAXN], t2[MAXN], t3[MAXN];
int dp[MAXS], ndp[MAXS];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    int sum_limit = 0;
    for (int i = 1; i <= n; i++) {
        cin >> t1[i] >> t2[i] >> t3[i];
        sum_limit += max(t1[i], t3[i]);
    }

    for (int i = 0; i <= sum_limit; i++) {
        dp[i] = INF;
    }
    dp[0] = 0;

    int cur_limit = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= sum_limit; j++) {
            ndp[j] = INF;
        }

        for (int a_time = 0; a_time <= cur_limit; a_time++) {
            if (dp[a_time] == INF) {
                continue;
            }

            // 当前任务只由 A 机器完成。
            if (t1[i] > 0) {
                ndp[a_time + t1[i]] = min(ndp[a_time + t1[i]], dp[a_time]);
            }

            // 当前任务只由 B 机器完成。
            if (t2[i] > 0) {
                ndp[a_time] = min(ndp[a_time], dp[a_time] + t2[i]);
            }

            // 当前任务由 A、B 两台机器共同完成。
            if (t3[i] > 0) {
                ndp[a_time + t3[i]] = min(ndp[a_time + t3[i]], dp[a_time] + t3[i]);
            }
        }

        cur_limit += max(t1[i], t3[i]);
        for (int j = 0; j <= cur_limit; j++) {
            dp[j] = ndp[j];
        }
    }

    int answer = INF;
    for (int a_time = 0; a_time <= cur_limit; a_time++) {
        if (dp[a_time] == INF) {
            continue;
        }
        answer = min(answer, max(a_time, dp[a_time]));
    }

    cout << answer << '\n';
    return 0;
}
