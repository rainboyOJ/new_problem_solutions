#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXX = 1005;

int n;                // 好友数量
int x;                // 药水数量
int lose_exp[MAXN];    // 失败时获得的经验
int win_exp[MAXN];     // 胜利时获得的经验
int need[MAXN];        // 打过至少需要的药水数量
long long dp[MAXX];    // dp[j] = 使用 j 瓶药水能获得的最大经验值

void read_input() {
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        cin >> lose_exp[i] >> win_exp[i] >> need[i];
    }
}

void solve() {
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= n; i++) {
        // 倒序枚举药水数，保证每个好友最多只打一次。
        // 使用 long long 防止中间结果溢出。
        for (int j = x; j >= 0; j--) {
            // 不打这个好友 → 获得失败经验
            dp[j] = dp[j] + lose_exp[i];
            // 打这个好友 → 比较胜利经验是否更大
            if (j >= need[i]) {
                // dp[j - need[i]] 是本轮更新前的值，即上一轮的结果
                dp[j] = max(dp[j], dp[j - need[i]] + win_exp[i]);
            }
        }
    }

    // 题目要求输出 5 × 最大经验
    cout << 5LL * dp[x] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
