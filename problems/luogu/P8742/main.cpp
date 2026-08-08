/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-08 23:13
 * update_at: 2026-08-08 23:13
 * 砝码可放左或右，用偏移量 (-sum~sum → 0~2*sum)
 */
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 5;
int n, sum;
int w[105];
bool dp[maxn];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> w[i];
        sum += w[i];
    }

    int offset = sum;
    dp[offset] = true;

    for (int i = 1; i <= n; ++i) {
        bool ndp[maxn] = {};
        for (int j = 0; j <= 2 * sum; ++j) {
            if (!dp[j]) continue;
            ndp[j] = true;
            ndp[j + w[i]] = true;
            ndp[j - w[i]] = true;
        }
        memcpy(dp, ndp, sizeof(dp));
    }

    int ans = 0;
    for (int j = offset + 1; j <= 2 * sum; ++j)
        if (dp[j]) ++ans;
    cout << ans << "\n";
    return 0;
}
