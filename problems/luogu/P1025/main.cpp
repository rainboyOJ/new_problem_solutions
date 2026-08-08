#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int n, k;
int dp[MAXN][10];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    // dp[s][cnt] 表示：
    // 把整数 s 划分成 cnt 份的方案数。
    // 外层按数字大小从小到大处理，相当于组合计数版完全背包，
    // 可以保证 1+2+4 和 4+2+1 只统计一次。
    dp[0][0] = 1;

    // part 表示当前允许加入的一个数字。
    for (int part = 1; part <= n; part++) {
        for (int sum = part; sum <= n; sum++) {
            for (int cnt = 1; cnt <= k; cnt++) {
                dp[sum][cnt] += dp[sum - part][cnt - 1];
            }
        }
    }

    cout << dp[n][k] << '\n';
    return 0;
}
