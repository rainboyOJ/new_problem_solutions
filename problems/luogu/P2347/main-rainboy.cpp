/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-06 20:35
 * update_at: 2026-09-06 20:35
 * 多重可行性背包，01 背包思维（普通 bool 数组）
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;         // 总重量上限
int cnt[6];                    // 每种砝码的数量
int w[6] = {1, 2, 3, 5, 10, 20}; // 六种砝码的重量
bool dp[MAXN];                 // dp[w] 表示重量 w 是否能被称出

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int sum = 0;
    for (int i = 0; i < 6; ++i) {
        cin >> cnt[i];
        sum += cnt[i] * w[i];
    }
    dp[0] = true;
    // 把每枚砝码看成一个独立的 0/1 物品（重量 = 价值）。逐枚展开后按 01 背包倒序转移。
    for (int i = 0; i < 6; ++i)
        for (int k = 0; k < cnt[i]; ++k)
            for (int j = sum; j >= w[i]; --j)
                if (dp[j - w[i]]) dp[j] = true;
    int ans = 0;
    for (int j = 1; j <= sum; ++j)
        if (dp[j]) ++ans;
    cout << "Total=" << ans << "\n";
    return 0;
}