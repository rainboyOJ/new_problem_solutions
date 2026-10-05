/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:45
 * update_at: 2026-10-05 12:45
 */
// 斜率优化 DP：转移展开成直线族 y = -2*T[j]*x + (dp[j]+T[j]^2)，
// 斜率与查询点双单调，用单调队列维护下凸壳，O(N) 求最小装箱费用。

#include <iostream>
using namespace std;

typedef long long ll;
typedef __int128 lll; // 凸壳比较的中间乘积可达 1e35，64 位整数会溢出

const int MAXN = 50005;

int n;
ll limit;
ll T[MAXN];  // T[i] = 前缀和 S[i] + i，由 C[i] >= 1 知其严格递增
ll dp[MAXN]; // dp[i] 表示前 i 件玩具的最小装箱费用
int q[MAXN]; // 单调队列：存直线对应的下标 j，斜率 -2*T[j] 随下标严格递减

// 第 j 条直线：y = -2*T[j] * x + (dp[j] + T[j]^2)，公共的 x^2 项统一后加
lll line_value(int j, ll x) {
    return (lll)(-2 * T[j]) * x + (lll)dp[j] + (lll)T[j] * T[j];
}

// 队首 a 在当前查询点已不优于 b：两条直线只有一个交点，追平后 a 永远更差
bool is_worse_front(int a, int b, ll x) {
    return line_value(a, x) >= line_value(b, x);
}

// b 被 a、c 夹成死线：交点 x_ab >= x_bc 时 b 取不到最小值，交叉相乘避免浮点
bool is_shadow(int a, int b, int c) {
    lll ya = (lll)dp[a] + (lll)T[a] * T[a];
    lll yb = (lll)dp[b] + (lll)T[b] * T[b];
    lll yc = (lll)dp[c] + (lll)T[c] * T[c];
    return (yb - ya) * (T[c] - T[b]) >= (yc - yb) * (T[b] - T[a]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> limit;
    for (int i = 1; i <= n; i++) {
        ll c;
        cin >> c;
        T[i] = T[i - 1] + c + 1; // 前缀和与下标各加 1
    }

    int head = 1, tail = 1;
    q[1] = 0; // j = 0：前 0 件玩具，T[0] = dp[0] = 0

    for (int i = 1; i <= n; i++) {
        ll x = T[i] - 1 - limit; // 断点为 j 时容器长度 = x - T[j]
        while (head < tail && is_worse_front(q[head], q[head + 1], x)) {
            head++; // x 随 i 递增，被追平的队首以后只会更差
        }
        int j = q[head];
        ll len = x - T[j]; // 该段容器长度与 limit 的差
        dp[i] = dp[j] + len * len; // 最优段的差恰为 dp[i]-dp[j]，不会溢出

        while (head < tail && is_shadow(q[tail - 1], q[tail], i)) {
            tail--; // 维护下凸壳：交点左移的尾线永远取不到最小值
        }
        q[++tail] = i;
    }

    cout << dp[n] << '\n';
    return 0;
}
