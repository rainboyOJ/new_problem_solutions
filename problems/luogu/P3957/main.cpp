/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:43
 * update_at: 2026-11-11 00:43
 */
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 500005;
const long long INF = 0x3f3f3f3f3f3f3f3fLL;

int n, d;
long long k;
long long x[MAXN];
long long s[MAXN];
long long dp[MAXN];
int q[MAXN]; // 手写单调队列存储决策点下标

// 检验花费 g 个金币是否能获得至少 k 分
bool check(long long g) {
    long long L = max(1LL, d - g);
    long long R = d + g;

    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = -INF;
    }

    int head = 0, tail = -1;
    int cur = 0; // 尝试入队的决策点指针

    for (int i = 1; i <= n; ++i) {
        // 1. 将所有满足 x[i] - x[cur] >= L 的决策点加入单调队列
        while (cur < i && x[i] - x[cur] >= L) {
            if (dp[cur] != -INF) {
                // 维护单调队列的单调递减性
                while (head <= tail && dp[q[tail]] <= dp[cur]) {
                    tail--;
                }
                q[++tail] = cur;
            }
            cur++;
        }

        // 2. 弹出过期的决策点：x[i] - x[q[head]] > R
        while (head <= tail && x[i] - x[q[head]] > R) {
            head++;
        }

        // 3. 从队头最优决策点转移
        if (head <= tail) {
            dp[i] = dp[q[head]] + s[i];
            if (dp[i] >= k) return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> d >> k)) return 0;

    long long sum_pos = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> x[i] >> s[i];
        if (s[i] > 0) sum_pos += s[i];
    }

    // 所有正分数累加都小于 k，必定无解
    if (sum_pos < k) {
        cout << -1 << "\n";
        return 0;
    }

    long long left = 0, right = max(x[n], static_cast<long long>(d));
    long long ans = -1;

    // 二分金币数 g
    while (left <= right) {
        long long mid = left + (right - left) / 2;
        if (check(mid)) {
            ans = mid;
            right = mid - 1; // 尝试更小的金币数
        } else {
            left = mid + 1;
        }
    }

    cout << ans << "\n";

    return 0;
}
