/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 18:45
 * update_at: 2026-08-28 18:45
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
long long k;                     // k 最大 n(n-1)/2 ≈ 5e9，必须用 long long
long long x[MAXN], y[MAXN];      // 每个点的 x_i, y_i
double p[MAXN], q[MAXN];         // p_i = x_i*(y_i-v)，q_i = x_i*(v-y_i) = -p_i

// 统计满足 f(i,j) >= v 的数对个数
long long check(double v) {
    long long tot = 0;
    for (int i = 1; i <= n; i++) {
        p[i] = x[i] * (y[i] - v);
        q[i] = x[i] * (v - y[i]);
        // 有向对 (i,i) 被计入当且仅当 p_i >= q_i（即 p_i >= 0），先减掉
        // 注意必须在排序前用原始下标判断
        if (q[i] - p[i] < 1e-3) tot--;
    }
    // 两个数组都升序排序，便于双指针统计 p_i >= q_j 的有向对数
    sort(p + 1, p + n + 1);
    sort(q + 1, q + n + 1);

    // 双指针：对每个 p[i]，统计满足 q[j] <= p[i] 的 j 的个数
    // p 升序时 p[i] 单调不减，j 也单调不减，整体 O(n)
    int j = 0;
    for (int i = 1; i <= n; i++) {
        while (j < n && q[j + 1] - p[i] < 1e-3) j++;
        tot += j;
    }
    // 每个合法无序对在有向计数中恰好贡献 2 次，折半即为答案
    return tot / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    // f(i,j) 是 y_i 与 y_j 以 x_i, x_j 为权的加权平均，取值恒在 [1, 1e9]
    double lo = 1, hi = 1e9;
    while (hi - lo > 1e-3) {
        double mid = (lo + hi) / 2;
        if (check(mid) >= k) lo = mid;
        else hi = mid;
    }
    printf("%.4f\n", lo);
    return 0;
}