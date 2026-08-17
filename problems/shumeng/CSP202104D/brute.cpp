/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
// brute.cpp：小数据暴力解，枚举每段的全部公差，直接检查是否经过内部障碍物。
#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> position(n + 1);
    vector<long long> dp(n + 1);
    for (int i = 1; i <= n; i++) cin >> position[i];
    dp[1] = 1;
    for (int left = 1; left < n; left++) {
        for (int right = left + 1; right <= n; right++) {
            int distance = position[right] - position[left];
            // 枚举公差 step：必须是距离的真因子，且不经过任何内部障碍物
            int ways = 0;
            for (int step = 1; step < distance; step++) {
                if (distance % step) continue;
                bool valid = true;
                for (int middle = left + 1; middle < right; middle++) {
                    if ((position[middle] - position[left]) % step == 0) valid = false;
                }
                if (valid) ways++;
            }
            dp[right] = (dp[right] + dp[left] * ways) % MOD;
        }
    }
    cout << dp[n] << '\n';

    return 0;
}