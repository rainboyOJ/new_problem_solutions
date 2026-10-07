/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:07
 * update_at: 2026-10-05 12:07
 */

// 二分答案 + 单调队列优化 DP。
// 判定：给定空题段上限 limit，求"任意连续 limit+1 题至少抄 1 道"方案的最小抄题总时间，
//       看它是否不超过总时间 t。可行域对 limit 单调不减，故二分最小可行 limit。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;

typedef long long ll;

int n;              // 题目总数
ll budget;          // 总时间上限 t
ll a[MAXN];         // a[i]：抄第 i 题要花的时间（1 开始编号）
ll dp[MAXN];        // dp[i]：第 i 题抄、且前 i 题空题段均不超过 limit 时的最小总时间
int que[MAXN];      // 单调队列，存下标 j；队内 dp 值递增，队首是窗口内 dp 最小的 j
int head, tail;     // 队列的左右端点，区间 [head, tail)

// 判断空题段上限为 limit 时是否能在 budget 内抄完。
bool feasible(int limit) {
    if (limit >= n) { // 一题都不抄：整段空题长度正好是 n，必可行
        return true;
    }

    // dp[0] = 0：虚拟起点"此前一题都没抄"。
    // 第 i 题与上一道抄的题 j 之间空了 i-j-1 题，要求 j >= i-limit-1，
    // 窗口下界自动管住了开头空段，无需特判。
    dp[0] = 0;
    que[0] = 0;
    head = 0;
    tail = 1;
    for (int i = 1; i <= n; i++) {
        while (que[head] < i - limit - 1) { // 队首滑出窗口 [i-limit-1, i-1]
            head++;
        }
        dp[i] = a[i] + dp[que[head]];
        while (head < tail && dp[que[tail - 1]] >= dp[i]) { // 维护队内 dp 单调递增
            tail--;
        }
        que[tail] = i;
        tail++;
    }

    // 末尾空段 n-i 也要 <= limit：最后一道抄的题 i 只需在 [n-limit, n] 里挑最小 dp。
    ll best = dp[n];
    for (int i = n - limit; i < n; i++) {
        if (dp[i] < best) {
            best = dp[i];
        }
    }
    return best <= budget;
}

void solve() {
    // 空题段越长越容易可行，二分最小可行 limit，lo == hi 即答案。
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (feasible(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    cout << lo << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> budget;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    solve();

    return 0;
}
