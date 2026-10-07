/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:35
 * update_at: 2026-10-06 13:35
 */
// 01 背包：dp[t] 表示总耗时不超过 t 时能采到的最大总价值
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXT = 1005;

ll dp[MAXT]; // dp[t]：容量（时间）为 t 时的最大总价值
ll c[105];   // c[i]：第 i 株草药的采摘耗时
ll v[105];   // v[i]：第 i 株草药的价值

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll T, M;
    cin >> T >> M;
    for (int i = 1; i <= M; i++)
        cin >> c[i] >> v[i];

    // 01 背包：每株草药只能采一次，容量必须倒序枚举，
    // 保证 dp[t - c[i]] 还是上一轮（没采过这株）的旧值
    for (int i = 1; i <= M; i++)
        for (ll t = T; t >= c[i]; t--)
            if (dp[t - c[i]] + v[i] > dp[t])
                dp[t] = dp[t - c[i]] + v[i];

    cout << dp[T] << endl;
    return 0;
}
