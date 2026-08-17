/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXA = 100000;
const long long MOD = 1000000007;

int n, position[MAXN];        // 障碍物坐标
int blocked[MAXA + 1];        // blocked[d] 记录把公差 d 标记为不可用的左端点，0 表示未标记
long long dp[MAXN];           // dp[r] 表示划分到第 r 个障碍物的方案数
vector<int> divisor[MAXA + 1]; // divisor[x] 为 x 的所有因数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> position[i];
    // 用调和级数预处理所有数的因数
    for (int d = 1; d <= MAXA; d++) {
        for (int value = d; value <= MAXA; value += d) divisor[value].push_back(d);
    }

    dp[1] = 1;
    for (int left = 1; left < n; left++) {
        // 固定左端点 left，从左到右枚举右端点 right
        for (int right = left + 1; right <= n; right++) {
            int distance = position[right] - position[left];
            // ways(l,r)：距离的真因子中未被内部障碍物阻塞的公差个数
            int ways = 0;
            for (int i = 0; i < (int)divisor[distance].size(); i++) {
                int step = divisor[distance][i];
                if (step != distance && blocked[step] != left) ways++;
            }
            dp[right] = (dp[right] + dp[left] * ways) % MOD;
            // 当前右端点对后续右端点来说变成内部障碍物，标记其所有因数为不可用
            for (int i = 0; i < (int)divisor[distance].size(); i++) blocked[divisor[distance][i]] = left;
        }
    }
    cout << dp[n] << '\n';

    return 0;
}