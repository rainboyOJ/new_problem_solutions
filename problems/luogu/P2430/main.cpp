#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXM = 105;
const int MAXT = 5005;

int wky_skill, wang_skill;
int m, n, limit_time;
int topic_time[MAXN]; // topic_time[i] 表示老王做知识点 i 的题所需时间
int cost[MAXM];       // cost[i] 表示 WKY 做第 i 道题需要的时间
int reward_value[MAXM];
int dp[MAXT];         // dp[t] 表示总时间不超过 t 时的最大奖励值

void read_input() {
    cin >> wky_skill >> wang_skill;
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        cin >> topic_time[i];
    }

    int ratio = wang_skill / wky_skill;
    for (int i = 1; i <= m; i++) {
        int p, q;
        cin >> p >> q;
        cost[i] = topic_time[p] * ratio;
        reward_value[i] = q;
    }
    cin >> limit_time;
}

void solve() {
    for (int i = 1; i <= m; i++) {
        // 0/1 背包必须倒序枚举时间，避免一题被重复选择。
        for (int t = limit_time; t >= cost[i]; t--) {
            dp[t] = max(dp[t], dp[t - cost[i]] + reward_value[i]);
        }
    }

    cout << dp[limit_time] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
