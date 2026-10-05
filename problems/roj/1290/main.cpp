/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:12
 * update_at: 2026-10-04 22:12
 */

// main.cpp：采药（roj 1290）的 0/1 背包一维滚动解。
// 容量上限 T <= 1000，物品数 M <= 100，单件花费与价值均在 [1,100]，结果用 long long 兜住。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXT = 1005; // 容量上限 + 1，足够放下题目给的最大 T

ll T;          // 总可用时间（背包容量）
ll M;          // 草药总数
ll dp[MAXT];   // dp[j] = 限定时间 j 内能采到的最大价值；只用一维滚动数组

void read_input() {
    cin >> T >> M;
}

void solve() {
    // 初始化：所有容量下的最优价值都为 0。
    for (ll j = 0; j <= T; j++) dp[j] = 0;

    for (ll i = 0; i < M; i++) {
        ll cost;   // 这株草药的采摘时间
        ll value;  // 这株草药的价值
        cin >> cost >> value;

        // 容量倒序扫描，保证 dp[j - cost] 还是上一轮（第 i-1 株）的结果，
        // 从而实现"每株草药至多取一次"的 0/1 语义。
        for (ll j = T; j >= cost; j--) {
            dp[j] = max(dp[j], dp[j - cost] + value);
        }
    }

    cout << dp[T] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}