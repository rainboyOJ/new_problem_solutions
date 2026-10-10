/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 02:20
 * update_at: 2026-10-08 02:20
 */
// main.cpp：分层图，状压 DP。只关心"源点到本层每个点的路径条数"的奇偶性，
// 于是 k<=10 个节点的奇偶向量可压成 2^k 个状态；层间取反等价于把 k×k 邻接矩阵转置，
// 每个状态向下一层分裂出"不取反 / 取反"两条转移。与 main.py 同一算法。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 998244353;   // 方案数的模数，与偶奇性所在的 GF(2) 无关
const int MAXK = 10;         // 题面 k<=10
const int MAXS = 1 << MAXK;  // 奇偶向量状态数上界 1024

int m, k;
int dp[MAXS], ndp[MAXS];     // 滚动数组：走到本层、奇偶向量恰为 mask 的取反前缀方案数
int rowBit[MAXK], colBit[MAXK]; // 本层邻接矩阵的行/列掩码（列掩码即转置矩阵的行掩码）
int goNo[MAXS], goYes[MAXS]; // goNo[v] = v*M，goYes[v] = v*M^T，均在 GF(2) 上

// 快读：输入规模最大约 m*k^2 = 10^6 个 0/1，scanf 亦可，这里统一成手写读入
int readInt() {
    int c = getchar_unlocked();
    while (c != EOF && (c < '0' || c > '9')) c = getchar_unlocked();
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = getchar_unlocked();
    }
    return x;
}

int main() {
    m = readInt();
    k = readInt();
    int N = 1 << k; // 奇偶向量的状态数

    // 第一行：源点到第 2 层各点的边，直接给出第 2 层的初始奇偶向量
    int startMask = 0;
    for (int t = 0; t < k; t++)
        if (readInt()) startMask |= 1 << t;

    fill(dp, dp + N, 0);
    dp[startMask] = 1; // 尚未做任何取反决策，方案数 1

    // 第 2..m-2 行：中间相邻两层的 k×k 邻接矩阵，这里可以取反（转置）
    for (int i = 2; i <= m - 2; i++) {
        fill(rowBit, rowBit + k, 0);
        fill(colBit, colBit + k, 0);
        for (int j = 0; j < k; j++)
            for (int t = 0; t < k; t++)
                if (readInt()) {
                    rowBit[j] |= 1 << t; // (i,j) -> (i+1,t)
                    colBit[t] |= 1 << j; // 取反后 (i,t) -> (i+1,j)：矩阵被转置
                }

        // go[s] = XOR_{j 在 s 中} (M 的第 j 行 / 第 j 列)，用 lowbit 按 2^k 递推出来
        goNo[0] = goYes[0] = 0;
        for (int s = 1; s < N; s++) {
            int low = s & -s;
            int j = __builtin_ctz(s);
            goNo[s] = goNo[s ^ low] ^ rowBit[j];
            goYes[s] = goYes[s ^ low] ^ colBit[j];
        }

        fill(ndp, ndp + N, 0);
        for (int v = 0; v < N; v++) {
            if (!dp[v]) continue;             // 到不了的状态不贡献方案
            int a = goNo[v], b = goYes[v];    // 不取反 / 取反，一次位运算得出，O(1)
            ndp[a] = (ndp[a] + dp[v]) % MOD;
            ndp[b] = (ndp[b] + dp[v]) % MOD;
        }
        copy(ndp, ndp + N, dp);
    }

    // 最后一行：第 m-1 层各点到汇点的边，这一段的取反是禁止的
    int endMask = 0;
    for (int t = 0; t < k; t++)
        if (readInt()) endMask |= 1 << t;

    // 路径总数 mod 2 = popcount(末层奇偶向量 & 汇点边掩码) mod 2，
    // 为 0（偶数条）的那些末态，其全部取反前缀方案都要计入答案
    ll ans = 0;
    for (int s = 0; s < N; s++)
        if (__builtin_popcount(s & endMask) % 2 == 0) ans += dp[s];
    printf("%lld\n", ans % MOD);
    return 0;
}
