/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 12:15
 * update_at: 2026-10-06 12:15
 */

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXV = 20005;

int dp[MAXV]; // dp[c]：只用已处理过的物品、容量 c 时能装下的最大总体积

int main() {
    int V; // 箱子容量
    int n; // 物品件数
    cin >> V >> n;

    // 0/1 背包：体积即价值，装入总体积越大，剩余空间越小
    for (int i = 1; i <= n; i++) {
        int w;
        cin >> w;
        // 倒序扫容量，保证每件物品最多被装入一次
        for (int c = V; c >= w; c--) {
            if (dp[c - w] + w > dp[c]) {
                dp[c] = dp[c - w] + w;
            }
        }
    }

    cout << V - dp[V] << endl; // 最小剩余空间
    return 0;
}
