#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int n, q_cnt;
int h[MAXN];
// dp[i]：到达第 i 棵树顶部时，最少需要多少次“疲劳跳跃”。
int dp[MAXN];
// 单调队列里存的是“可能成为最优前驱”的树编号。
int que[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    cin >> q_cnt;
    while (q_cnt--) {
        int k;
        cin >> k;

        int head = 1, tail = 1;
        dp[1] = 0;
        que[1] = 1;

        for (int i = 2; i <= n; i++) {
            // 只能从区间 [i-k, i-1] 里的树飞过来。
            while (head <= tail && que[head] < i - k) {
                head++;
            }

            int best = que[head];
            // 如果终点高度不低于起点，这一跳就会增加一次“疲劳跳跃”。
            dp[i] = dp[best];
            if (h[best] <= h[i]) {
                dp[i]++;
            }

            // 维护一个“候选起点队列”：
            // 1. dp 更小的一定更优
            // 2. 若 dp 相同，则高度更高的更优，因为它更容易形成“不疲劳”的下降跳跃
            while (head <= tail) {
                int last = que[tail];
                if (dp[last] > dp[i] || (dp[last] == dp[i] && h[last] <= h[i])) {
                    tail--;
                } else {
                    break;
                }
            }
            que[++tail] = i;
        }

        cout << dp[n] << '\n';
    }

    return 0;
}
