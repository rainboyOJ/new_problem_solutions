/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-06 22:43
 * update_at: 2026-08-06 22:58
 */

// P3509 [POI 2010] ZAB-Frog
// 每个石头一步跳到距它第 k 近的石头（平局取离源头最近），
// 求每个起点跳 m 次后的位置。
//
// 思路：
// 1) 双指针 O(n) 求出每个石头的单步目标 nxt[i]；
// 2) 把"跳一步"看成函数 f，用二进制倍增（映射的快速幂）求 f^m。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int n, k;
long long m;           // 跳跃次数，最大 1e18
long long p[MAXN];     // 石头位置，严格递增

int nxt[MAXN];         // nxt[i]：从石头 i 跳一步到达的石头编号
int F[MAXN];           // 倍增滚动数组，F[i] 表示当前层 2^j 步能到达的石头
int TMP[MAXN];         // 平方时使用的临时数组
int ANS[MAXN];         // ANS[i]：从 i 出发已走完低位块后的位置

// 用双指针求所有石头的一步目标。
// 关键观察：离石头 i 最近的 k+1 块石头（含 i 自己）在有序数组中构成连续窗口 [l, r]；
// 第 k 近的石头就是窗口中离 i 较远的那个端点（两端距离相等时取左端，即离源头最近）。
void calc_next() {
    int l = 1;
    int r = k + 1;      // 初始窗口 [1, k+1]，保证第 1 块石头右边有 k 块
    for (int i = 1; i <= n; i++) {
        // 右边下一个石头比左端点更近时，整个窗口右移一格。
        // l、r 只增不减，所以总移动次数为 O(n)。
        while (r + 1 <= n && p[r + 1] - p[i] < p[i] - p[l]) {
            l++;
            r++;
        }
        if (p[r] - p[i] > p[i] - p[l]) {
            nxt[i] = r;   // 右端点严格更远，第 k 近在右边
        } else {
            nxt[i] = l;   // 左端点更远或两端等距，取左端（离源头最近）
        }
    }
}

// 映射的快速幂：对每个起点求 f^m 后的位置，结果写入 ANS。
// 与 rbook 模板 quick-pow 同构：m 的每一位为 1 时把当前层 f^(2^j) 作用到答案上，
// 每层再把函数平方成 f^(2^(j+1))（F[F[i]] 相当于映射合成两次）。
// 调用前要求 F 初始化为 f^1，ANS 初始化为原地（0 步）。
void jump_power(long long m) {
    while (m > 0) {
        if (m & 1) {                              // 当前 2^j 这一位是 1，走这一块
            for (int i = 1; i <= n; i++) {
                ANS[i] = F[ANS[i]];
            }
        }
        for (int i = 1; i <= n; i++) {             // 平方：f^(2^(j+1)) = f^(2^j) 两次
            TMP[i] = F[F[i]];
        }
        for (int i = 1; i <= n; i++) {
            F[i] = TMP[i];
        }
        m >>= 1;
    }
}

void read_input() {
    scanf("%d%d%lld", &n, &k, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &p[i]);
    }
}

void solve() {
    calc_next();

    // 每个点只有一条出边，所以"跳 2^j 步"可以当函数整体平方。
    for (int i = 1; i <= n; i++) {
        F[i] = nxt[i];     // 第 0 层：1 步
        ANS[i] = i;        // 0 步：还在原地
    }
    jump_power(m);         // 从低位到高位拼出 m 步

    for (int i = 1; i <= n; i++) {
        if (i > 1) printf(" ");
        printf("%d", ANS[i]);
    }
    printf("\n");
}

int main() {
    read_input();
    solve();
    return 0;
}
