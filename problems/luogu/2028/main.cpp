/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-09 09:44
 * update_at: 2026-07-09 09:47
 */
// main.cpp：第二类斯特林数递推，滚动数组优化。
#include <bits/stdc++.h>
using namespace std;

const int MAXK = 1005;

int n, k;
long long p;
long long dp[MAXK];  // dp[j] 表示当前处理完若干苹果后，放成 j 个非空篮子的方案数。
long long ndp[MAXK]; // ndp[j] 表示下一层转移后的方案数。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> p;

    dp[0] = 1 % p;

    for (int i = 1; i <= n; i++) {
        int upper = min(i, k);
        for (int j = 0; j <= upper; j++) {
            ndp[j] = 0;
        }

        for (int j = 1; j <= upper; j++) {
            // 第 i 个苹果单独开一个新篮子，或者放进已有的 j 个篮子之一。
            __int128 ways = dp[j - 1];
            ways += (__int128)j * dp[j];
            ndp[j] = (long long)(ways % p);
        }

        for (int j = 0; j <= upper; j++) {
            dp[j] = ndp[j];
        }
    }

    cout << dp[k] % p << '\n';
    return 0;
}
