/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:55
 * update_at: 2026-10-05 12:55
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 500005;

// 注意值域：N <= 5*10^5，C 为非负权值，前缀和、dp 均在 ll 范围内
ll C[MAXN];  // 每个单词的权值
ll S[MAXN];  // S[i] = 前 i 个单词的权值和
ll dp[MAXN]; // dp[i]：前 i 个单词分段打印的最小费用
int q[MAXN]; // 单调队列：保存凸壳上的决策下标，x 坐标 S[j] 严格递增
int head, tail; // 队列有效区间 [head, tail)

// 凸壳上点 j 的纵坐标：由转移式移项得到 y(j) = dp[j] + S[j]^2
inline ll y_of(int j) {
    return dp[j] + S[j] * S[j];
}

int main() {
    int n;
    ll m;
    // 多组数据，读到文件末尾为止
    while (scanf("%d %lld", &n, &m) == 2) {
        if (n == 0) { // 一个单词都不用打印，费用为 0
            printf("0\n");
            continue;
        }

        for (int i = 1; i <= n; ++i) {
            scanf("%lld", &C[i]);
            S[i] = S[i - 1] + C[i];
        }

        // 决策下标 0（一个单词都不选）先入队
        head = 1; tail = 1;
        q[tail++] = 0;

        for (int i = 1; i <= n; ++i) {
            ll k = 2 * S[i]; // 当前决策直线的斜率，随 i 单调不减

            // 队头：相邻两点斜率 <= k 时，队头不再可能是最优决策，弹出
            while (tail - head >= 2 &&
                   (y_of(q[head + 1]) - y_of(q[head])) <= k * (S[q[head + 1]] - S[q[head]])) {
                ++head;
            }

            // 队头即最优决策
            int j = q[head];
            ll d = S[i] - S[j];
            dp[i] = dp[j] + d * d + m;

            // 队尾：弹出破坏下凸壳（斜率不严格递增）的点
            // 斜率比较全部用交叉相乘，避免除法和除零
            while (tail - head >= 2 &&
                   (y_of(q[tail - 1]) - y_of(q[tail - 2])) * (S[i] - S[q[tail - 2]]) >=
                   (y_of(i) - y_of(q[tail - 2])) * (S[q[tail - 1]] - S[q[tail - 2]])) {
                --tail;
            }

            // C_i = 0 会导致 S[i] = S[q[tail-1]]（x 重复）：
            // 此时 dp 非降，新点 y 更大，被旧点完全覆盖，直接不入队
            if (S[i] > S[q[tail - 1]]) {
                q[tail++] = i;
            }
        }

        printf("%lld\n", dp[n]);
    }
    return 0;
}
