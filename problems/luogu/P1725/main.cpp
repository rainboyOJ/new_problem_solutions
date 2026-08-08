#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int NEG_INF = -1000000000;

int n, l, r;
int a[MAXN];
int dp[MAXN];  // dp[i] 表示到达格子 i 时能获得的最大冰冻指数。
int que[MAXN]; // 单调队列存可作为起跳点的下标，队头 dp 最大。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> l >> r;
    for (int i = 0; i <= n; i++) {
        cin >> a[i];
        dp[i] = NEG_INF;
    }
    dp[0] = 0;

    int head = 1, tail = 0;
    int ans = NEG_INF;

    for (int i = l; i <= n; i++) {
        int candidate = i - l;
        if (dp[candidate] != NEG_INF) {
            // 新加入的起跳点若更优，就弹掉队尾较差点。
            while (head <= tail && dp[que[tail]] <= dp[candidate]) {
                tail--;
            }
            tail++;
            que[tail] = candidate;
        }

        // 当前格子 i 只能由 [i-r, i-l] 中的点跳来。
        while (head <= tail && que[head] < i - r) {
            head++;
        }

        if (head <= tail) {
            dp[i] = dp[que[head]] + a[i];
        }

        // 从 i 再跳一步，只要最大跳跃距离能越过 n，就可以作为最后停留点。
        if (i + r > n && dp[i] > ans) {
            ans = dp[i];
        }
    }

    cout << ans << '\n';

    return 0;
}
