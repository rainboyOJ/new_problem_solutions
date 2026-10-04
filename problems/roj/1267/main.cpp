/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:39
 * update_at: 2026-10-05 07:39
 */

// 01 背包：一维滚动数组，容量倒序扫描保证每件物品最多选一次。
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 35;    // 物品数上限
const int MAXM = 205;   // 背包容量上限

ll m, n;                // 背包容量、物品数量
ll w[MAXN], c[MAXN];    // w[i] 第 i 件物品重量，c[i] 第 i 件物品价值
ll dp[MAXM];            // dp[v]：容量不超过 v 时能获得的最大价值

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> m >> n;
    for (int i = 1; i <= n; i++)
        cin >> w[i] >> c[i];

    // 转移：dp[v] = max(dp[v], dp[v-w]+c)，v 必须从大到小扫描。
    // 倒序时 dp[v-w] 还没被本轮更新，是"没考虑本物品"的旧值；
    // 正序会让同一件物品被反复装入，变成完全背包。
    for (int i = 1; i <= n; i++)
        for (int v = (int)m; v >= (int)w[i]; v--)
            dp[v] = max(dp[v], dp[v - w[i]] + c[i]);

    cout << dp[m] << endl;
    return 0;
}
