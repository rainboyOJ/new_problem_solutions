/**
 * Author by Rainboylv blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:52
 * update_at: 2026-10-05 11:52
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

typedef long long ll;

ll n;
ll k;
ll e[MAXN];   // e[i]：第 i 只奶牛的效率
ll s[MAXN];   // s[i]：前缀和，s[i] = e[1] + ... + e[i]
ll dp[MAXN];  // dp[i]：前 i 只奶牛、无超过 k 只连续被选的最大效率和
ll q[MAXN];   // 单调队列存候选断点 j，队首到队尾下标递增、h 值递减
ll h(int j) { // 候选值 h(j) = dp[j-1] - s[j]，只含 j，用于拆项
    return dp[j - 1] - s[j];
}

// 单调队列优化的一维 DP，求无超过 k 连续被选奶牛的最大效率和。
void solve() {
    s[0] = 0;
    for (ll i = 1; i <= n; i++) s[i] = s[i - 1] + e[i];

    // 先把候选 j=0（从头开始选，dp[-1] 视为 0）入队
    int head = 1, tail = 1; // 队列区间 [head, tail)，head==tail 表示空
    q[tail++] = 0;

    for (ll i = 1; i <= n; i++) {
        // 队首过期：断点 j 必须满足 i - k <= j <= i - 1
        while (head < tail && q[head] < i - k) head++;

        // 选到 i：断点 j=i 时不选任何奶牛，对应 dp[i-1]
        dp[i] = dp[i - 1];
        if (head < tail) {
            ll best = s[i] + h(q[head]);
            if (best > dp[i]) dp[i] = best;
        }

        // 入队候选 j=i，队尾弹出所有 h 值不大于它的候选（下标更大、值更小，永远轮不到）
        ll value = h(i);
        while (head < tail && h(q[tail - 1]) <= value) tail--;
        q[tail++] = i;
    }
    cout << dp[n] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    for (ll i = 1; i <= n; i++) cin >> e[i];
    solve();
    return 0;
}
