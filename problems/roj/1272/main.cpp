/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:44
 * update_at: 2026-10-05 07:44
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXV = 205; // 背包容量上限
const int MAXN = 35;  // 物品数量上限

ll V, N, T;
ll w[MAXN], c[MAXN], grp[MAXN]; // 每件物品的重量、价值、所属组号
ll dp[MAXV]; // dp[cap]：只考虑已处理完的组、容量不超过 cap 时的最大价值

int main() {
    cin >> V >> N >> T;
    for (int i = 1; i <= N; i++)
        cin >> w[i] >> c[i] >> grp[i];

    // 分组背包：外层枚举组，容量倒序，最内层枚举组内物品
    // 容量倒序保证每轮转移只读「上一组处理完」的旧值，
    // 同组两件物品不会在同一个格子里叠加，天然满足每组最多选一件
    for (int g = 1; g <= T; g++)
        for (int cap = V; cap >= 0; cap--)
            for (int i = 1; i <= N; i++)
                if (grp[i] == g && w[i] <= cap)
                    dp[cap] = max(dp[cap], dp[cap - w[i]] + c[i]);

    // dp[cap] 关于 cap 单调不减，容量上限处就是答案
    cout << dp[V] << endl;
    return 0;
}
