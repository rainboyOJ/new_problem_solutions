/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:17
 * update_at: 2026-10-05 08:17
 */

// 装箱问题：体积既是重量也是收益的 0/1 背包，
// 求不超过容量 V 的最大可拼出体积 S，输出剩余空间 V - S。

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXV = 20005;

int dp[MAXV]; // dp[s] = 1 表示体积 s 能被若干已处理物品恰好拼出，否则为 0

int main() {
    ll capacity;
    ll n;
    cin >> capacity >> n;

    dp[0] = 1; // 一个物品都不选时体积 0 可达

    for (ll i = 1; i <= n; i++) {
        ll w;
        if (!(cin >> w)) {
            break; // 实测数据可能不足 n 个体积，读不到就结束
        }
        if (w > capacity) {
            continue; // 单个物品就超过容量，任何方案都装不下它
        }
        // 0/1 背包：从大到小枚举，保证每个物品只用一次
        for (ll s = capacity; s >= w; s--) {
            if (dp[s - w]) {
                dp[s] = 1;
            }
        }
    }

    // 从大到小找第一个可达体积，就是最多能装下的体积
    ll best = 0;
    for (ll s = capacity; s >= 0; s--) {
        if (dp[s]) {
            best = s;
            break;
        }
    }

    cout << capacity - best << endl;
    return 0;
}
