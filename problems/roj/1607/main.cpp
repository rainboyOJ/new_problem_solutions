// main.cpp：任务安排 2，斜率优化 DP 标准模板（单调队列维护下凸壳，O(n)）。

/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:41
 * update_at: 2026-10-05 10:41
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 1e4 + 5;

ll n;              // 任务数
ll s;              // 每批的启动时间
ll t[MAXN], c[MAXN];   // t[i] 第 i 个任务耗时，c[i] 第 i 个任务费用系数
ll pret[MAXN], prec[MAXN]; // pret/prec：耗时与费用系数的前缀和，下标 0 处为 0
ll f[MAXN];        // f[i]：前 i 个任务分批的最小总费用
ll y[MAXN];        // y[j]：决策点 j 的纵坐标（见下方转移说明）
int q[MAXN];       // 单调队列：保存下凸壳上决策点的编号
int head, tail;    // 队头、队尾（左闭右开 [head, tail)）

// 判断队头决策是否已被次队头完全超越：用纵坐标差与横坐标差的叉积代替斜率除法。
// a、b 是队头前两个决策点，k 是本轮查询斜率 pret[i]。
bool head_worse(int a, int b, ll k) {
    return y[b] - k * prec[b] <= y[a] - k * prec[a];
}

// 判断新点 i 加入后，队尾决策点 b 是否被线段 a-i 盖住（破坏下凸性）。
bool tail_bad(int a, int b, int i) {
    return (y[b] - y[a]) * (prec[i] - prec[b]) >= (y[i] - y[b]) * (prec[b] - prec[a]);
}

int main() {
    scanf("%lld", &n);
    scanf("%lld", &s);
    for (int i = 1; i <= (int)n; i++) {
        scanf("%lld %lld", &t[i], &c[i]);
        pret[i] = pret[i - 1] + t[i];
        prec[i] = prec[i - 1] + c[i];
    }

    // 换记账次序：把启动时间 S 提前算进后续所有任务的费用，
    // 转移化为 f[i] = pret[i]*prec[n] + min_j { y[j] - pret[i]*prec[j] }，
    // 即用斜率 k = pret[i] 的直线去切决策点集 {(prec[j], y[j])} 的下凸壳。
    ll total_c = prec[n];
    f[0] = 0;
    y[0] = s * total_c; // j = 0 的纵坐标：f[0] - pret[0]*(total_c-prec[0]) + s*(total_c-prec[0])
    head = 0;
    tail = 0;
    q[tail++] = 0; // 初始决策点 j = 0 入队

    for (int i = 1; i <= (int)n; i++) {
        ll k = pret[i]; // 本轮查询斜率，因 T_i > 0 随 i 单调递增
        // 队头不再最优：因 k 单调增，被超越后永远用不到，直接弹出
        while (head + 1 < tail && head_worse(q[head], q[head + 1], k))
            head++;
        int j = q[head];
        f[i] = k * total_c + y[j] - k * prec[j];
        // 新决策点 i 的纵坐标（f[i] 代入换记账次序的展开式）
        y[i] = f[i] - pret[i] * (total_c - prec[i]) + s * (total_c - prec[i]);
        // 新点横坐标 prec[i] 单调递增，只需从队尾弹出破坏凸性的旧点
        while (head + 1 < tail && tail_bad(q[tail - 2], q[tail - 1], i))
            tail--;
        q[tail++] = i;
    }

    printf("%lld\n", f[n]);
    return 0;
}
