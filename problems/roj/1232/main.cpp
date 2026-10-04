/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:04
 * update_at: 2026-10-05 06:04
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 1005;
ll a[MAXN]; // a[i] 表示第 i 个人单独划船过河所需的时间，已按升序排列

// 求把 a[0..n-1] 全部送到对岸的最少总时间。
// 每次只送走当前最慢的人，有两种剧本：最快者往返快递一人，或两名最快者摆渡两名最慢者。
ll crossing_river(int n) {
    if (n == 1) {
        return a[0]; // 只剩一人，他自己划过去
    }
    ll dp_prev2 = a[0]; // dp[0]：只有一个人的花费
    ll dp_prev1 = a[1]; // dp[1]：两人一起过去，耗时由慢者决定
    for (int i = 2; i < n; i++) {
        // 方案 A：最快者送最慢者过去，自己再划回来，本轮只送走一人
        ll solo = dp_prev1 + a[0] + a[i];
        // 方案 B：两名最快者先把船送到对岸，两名最慢者同船过去，本轮送走两人
        ll duo = dp_prev2 + a[0] + 2 * a[1] + a[i];
        ll best = min(solo, duo);
        dp_prev2 = dp_prev1;
        dp_prev1 = best;
    }
    return dp_prev1; // 即 dp[n-1]
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        // 先排序：只有有序，"当前最慢的人"才是末尾那个人
        sort(a, a + n);
        cout << crossing_river(n) << "\n";
    }
    return 0;
}
