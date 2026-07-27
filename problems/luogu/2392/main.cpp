/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

int s[4];
int t[4][25];
int dp[1500]; // dp[i] = 1 表示能凑出时间 i

int subject_time(int times[], int len) {
    int total = 0;
    for (int i = 0; i < len; i++) total += times[i];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int i = 0; i < len; i++)
        for (int j = total; j >= times[i]; j--)
            if (dp[j - times[i]]) dp[j] = 1;
    int best = total;
    for (int left = 0; left <= total; left++)
        if (dp[left]) best = min(best, max(left, total - left));
    return best;
}

int main() {
    for (int i = 0; i < 4; i++) cin >> s[i];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < s[i]; j++) cin >> t[i][j];
    int ans = 0;
    for (int i = 0; i < 4; i++) ans += subject_time(t[i], s[i]);
    cout << ans << endl;
    return 0;
}
