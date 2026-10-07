// 1742 导线问题
// 一本通 · 高手训练篇（四、数据结构）—— 与经典题「降雷皇」题面一致
//
// 题意：给定长度 n 的序列 a[1..n]，求最长严格上升子序列的长度 L；
//       若 type=1，再输出长度恰为 L 的严格上升子序列个数（按“下标位置”计数，
//       同一数值出现在不同位置视为不同方案），答案对 123456789 取模。
//
// 算法：树状数组（BIT）维护值域上的可合并信息 (len, cnt)
//       dp[i] = 以 i 结尾的最优信息 = merge(值域上「严格小于 a[i]」的前缀) 再 (len+1)
//       合并规则：len 大者胜；len 相等时 cnt 相加（取模）；两侧都是空序列（len==0）
//       时代表“一条都不选”，方案数为 1（哨兵/单位元）。
//       该合并满足结合律、交换律且以 (0,1) 为单位元，故 BIT 前缀查询正确。
//       值域先离散化，严格上升 ⇔ 查询 rank-1 的前缀。
//
// 复杂度：时间 O(n log n)，空间 O(n)。
//
// 编译：/opt/homebrew/bin/g++-16 -O2 -std=c++17 -o main main.cpp

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 123456789;  // 题目要求的模数
const int MAXN = 100005;    // n 的上限

int n, type_;
int a[MAXN];      // 原序列
int val[MAXN];    // 离散化用的有序去重值
int bitLen[MAXN]; // 值域 BIT：最长长度
int bitCnt[MAXN]; // 值域 BIT：该长度下的方案数

// 合并两段值域信息：长度大者胜，长度相等则方案数相加
// 特判：两侧长度都为 0 表示区间为空，方案数保持 1
inline void mergeInto(int &len, int &cnt, int l2, int c2) {
    if (l2 > len) {
        len = l2;
        cnt = c2;
    } else if (l2 == len && len > 0) {
        cnt += c2;
        if (cnt >= MOD) cnt -= MOD;
    }
}

int main() {
    scanf("%d %d", &n, &type_);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        val[i] = a[i];
    }

    // 离散化：rank ∈ [1, K]
    sort(val + 1, val + n + 1);
    int K = (int)(unique(val + 1, val + n + 1) - val - 1);

    // BIT 初始化：每个位置都是“空序列”，长度 0、方案数 1
    for (int i = 1; i <= K; i++) {
        bitLen[i] = 0;
        bitCnt[i] = 1;
    }

    for (int i = 1; i <= n; i++) {
        int r = (int)(lower_bound(val + 1, val + K + 1, a[i]) - val); // 当前值的 rank
        // 查询取值严格小于 a[i] 的部分（rank ∈ [1, r-1]）
        int bestLen = 0, bestCnt = 1;
        for (int j = r - 1; j > 0; j -= j & (-j)) {
            mergeInto(bestLen, bestCnt, bitLen[j], bitCnt[j]);
        }
        // 接在最优前缀后面，构成以 i 结尾的上升子序列
        int curLen = bestLen + 1;
        int curCnt = bestCnt;
        // 把 dp[i] 合并进值域位置 r
        for (int j = r; j <= K; j += j & (-j)) {
            mergeInto(bitLen[j], bitCnt[j], curLen, curCnt);
        }
    }

    // 全局答案 = 整个值域前缀 [1, K] 的合并结果
    int ansLen = 0, ansCnt = 1;
    for (int j = K; j > 0; j -= j & (-j)) {
        mergeInto(ansLen, ansCnt, bitLen[j], bitCnt[j]);
    }

    printf("%d\n", ansLen);
    if (type_ == 1) printf("%d\n", ansCnt);
    return 0;
}
