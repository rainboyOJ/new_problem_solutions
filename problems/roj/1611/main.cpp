/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:44
 * update_at: 2026-10-05 12:50
 */
// ZJOI 2007 仓库建设：分段 DP + 斜率优化（单调队列维护下凸壳），O(N)。
// dp[i]：前 i 个工厂处理完且第 i 个建仓库的最小费用；产品只能往编号更大的方向运。
#include <cstdio>

typedef long long ll;

const int MAXN = 1000005;

// 每个工厂：位置、产品数、建仓费（N 最大 1e6，开全局数组避免爆栈）
ll x[MAXN];
ll p[MAXN];
ll c[MAXN];

// 下凸壳用数组模拟队列：slope/intercept 保存每条决策直线 y = m*x + b
// 决策点 j（dp[j]，j 可为 0 哨兵）对应斜率 m = -W[j]，截距 b = dp[j] + D[j]
ll q_slope[MAXN];
ll q_intercept[MAXN];
int head = 0; // 队头下标，只前进
int tail = 0; // 队尾下标（开区间），新直线插在 tail 处

ll w_sum[MAXN]; // w_sum[j] = P_1 + ... + P_j（前缀和，W[j]）
ll d_sum[MAXN]; // d_sum[j] = P_1*X_1 + ... + P_j*X_j（前缀和，D[j]）
ll dp[MAXN];    // dp[i]：第 i 个工厂一定建仓库时的最小费用，dp[0] = 0

// 把决策点（斜率 m、截距 b）加入队尾
// 队列内斜率严格递减：先消掉与末线平行的情形（P 可为 0，W 不严格递增），再弹被盖住的末线
void push_line(ll m, ll b) {
    // 斜率相同时两条平行线只剩截距更小的一条
    while (tail > head && q_slope[tail - 1] == m) {
        if (b >= q_intercept[tail - 1]) return; // 新线永不更优，直接丢弃
        tail--;
    }
    while (tail - head >= 2) {
        // 末线被盖住 <=> 旧两线交点横坐标 x12 >= 末线与新线交点横坐标 x23
        // x12 = (b_last - b_prev) / (m_prev - m_last)，x23 = (b - b_last) / (m_last - m)
        // 此时两个分母都为正（斜率严格递减），交叉相乘避免除法
        if ((q_intercept[tail - 1] - q_intercept[tail - 2]) * (q_slope[tail - 1] - m)
                >= (b - q_intercept[tail - 1]) * (q_slope[tail - 2] - q_slope[tail - 1]))
            tail--;
        else
            break;
    }
    q_slope[tail] = m;
    q_intercept[tail] = b;
    tail++;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld %lld", &x[i], &p[i], &c[i]);
    }

    // 哨兵决策点 j = 0：dp[0] = 0，W[0] = D[0] = 0，对应直线 y = 0（截距 0）
    dp[0] = 0;
    w_sum[0] = 0;
    d_sum[0] = 0;
    head = tail = 0;
    push_line(0, 0);

    for (int i = 1; i <= n; i++) {
        // 转移：dp[i] = c[i] + x[i]*W[i-1] - D[i-1] + min_j { -W[j]*x[i] + dp[j] + D[j] }
        // 推导：(j, i] 段运费 = x[i]*(W[i-1]-W[j]) - (D[i-1]-D[j])，i 自己的产品运费为 0

        // 查询点 x[i] 单调递增：队头一旦不优于第二条，之后也不会翻身
        while (tail - head >= 2
                && q_slope[head] * x[i] + q_intercept[head]
                   >= q_slope[head + 1] * x[i] + q_intercept[head + 1])
            head++;

        ll best = q_slope[head] * x[i] + q_intercept[head]; // min 部分取到的是 dp[j] + D[j]
        dp[i] = c[i] + x[i] * w_sum[i - 1] - d_sum[i - 1] + best;

        // 插入新决策点 j = i：W 单调不减 => 斜率 -W[i] 单调不增，永远插在队尾
        w_sum[i] = w_sum[i - 1] + p[i];       // W[i] = sum_{t<=i} P_t
        d_sum[i] = d_sum[i - 1] + p[i] * x[i]; // D[i] = sum_{t<=i} P_t*X_t
        push_line(-w_sum[i], dp[i] + d_sum[i]);
    }

    // 题面保证产品运往山脚工厂 N，所以 S 必须包含 N，答案就是 dp[N]
    printf("%lld\n", dp[n]);
    return 0;
}
