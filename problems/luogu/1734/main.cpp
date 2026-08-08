/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-08 23:13
 * update_at: 2026-08-08 23:13
 * 预处理约数和，01背包选数使约数和最大
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 1005;
int s;
int val[maxn];
int dp[maxn];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> s;

    for (int i = 1; i <= s; ++i) {
        if (i > 1) val[i] = 1;
        for (int d = 2; d * d <= i; ++d) {
            if (i % d) continue;
            val[i] += d;
            if (d * d != i)
                val[i] += i / d;
        }
    }

    for (int i = 1; i <= s; ++i)
        for (int j = s; j >= i; --j)
            dp[j] = max(dp[j], dp[j - i] + val[i]);

    cout << dp[s] << "\n";
    return 0;
}
