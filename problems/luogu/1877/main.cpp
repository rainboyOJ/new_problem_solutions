/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-08 23:13
 * update_at: 2026-08-08 23:13
 * dp[i][j] 表示前i首可达音量j
 */
#include <bits/stdc++.h>
using namespace std;

const int maxl = 1005;
int n, bg, mx;
bool dp[55][maxl];

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> bg >> mx;
    dp[0][bg] = true;
    for (int i = 1; i <= n; ++i) {
        int c; cin >> c;
        for (int j = 0; j <= mx; ++j) {
            if (!dp[i - 1][j]) continue;
            if (j + c <= mx) dp[i][j + c] = true;
            if (j - c >= 0) dp[i][j - c] = true;
        }
    }
    for (int j = mx; j >= 0; --j)
        if (dp[n][j]) { cout << j << "\n"; return 0; }
    cout << "-1\n";
    return 0;
}
