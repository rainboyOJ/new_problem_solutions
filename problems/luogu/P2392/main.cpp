/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:20
 * update_at: 2026-08-13 13:20
 */
// main.cpp：每科独立求最优耗时，用 0/1 背包一维子集和 DP，
// 找不超过总时间一半的最大可达左脑时间，答案取另一边的总时间。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;     // 每科最多 20 道题
const int MAXSUM = 1500; // 每科总时间上限 20 * 60 = 1200

int s[4];          // s[i] 表示第 i 科的题目数量
int t[4][MAXN];    // t[i][j] 表示第 i 科第 j 道题的耗时
int dp[MAXSUM];    // dp[j] = 1 表示用当前科的题目能凑出左脑时间 j

// 求一科的最短耗时：把题目分给左右两组，使两组总时间的较大值最小。
int subject_time(int times[], int len) {
    int total = 0;
    for (int i = 1; i <= len; i++) total += times[i];

    // 0/1 背包一维子集和：dp[j] 由 dp[j - times[i]] 转移而来
    memset(dp, 0, sizeof(dp));
    dp[0] = 1; // 一道题都不给左脑
    for (int i = 1; i <= len; i++)
        // 逆序枚举，保证每道题只用一次（0/1 背包的写法）
        for (int j = total; j >= times[i]; j--)
            if (dp[j - times[i]]) dp[j] = 1;

    // 找不超过 total/2 的最大可达 left，
    // 此时另一组时间是 total - left，这一科耗时就是它。
    int left = total / 2;
    while (dp[left] == 0) left--;
    return total - left;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 4; i++) cin >> s[i];
    for (int i = 0; i < 4; i++)
        for (int j = 1; j <= s[i]; j++) cin >> t[i][j];

    int ans = 0;
    for (int i = 0; i < 4; i++) ans += subject_time(t[i], s[i]);
    cout << ans << '\n';
    return 0;
}
