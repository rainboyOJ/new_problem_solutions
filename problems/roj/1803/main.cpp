/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 04:05
 * update_at: 2026-10-08 04:05
 */
// main.cpp：列数字（ROJ 1803）。给 1..N 的一个置换，反复写下一排直到回到 1..N，
// 排数 = 置换阶 + 1，置换阶 = 各轮换长度的 lcm，轮换长度是 N 的一个分拆（长度和 ≤ N）。
// 于是「可能的排数个数」= 分拆的 lcm 的不同取值个数。由唯一分解定理，lcm 只由各素数
// 取到的最大幂次决定，故一个可达 lcm ↔ 一组「每个素数至多取一个幂 p^a，幂和 ≤ N」的选取，
// 且不同选取给出不同乘积（无重复），答案就是这些选取的方案数，含空集（lcm=1，排数=2）。
// 算法：按素数组的有界背包计数 dp[j] = 取出的素数幂之和恰为 j 的方案数。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005; // N 的上界（题面 1 ≤ N ≤ 1000），数组多开一点防越界

typedef long long ll;

bool notPrime[MAXN]; // 埃氏筛的合数标记
int primes[MAXN];    // [2, N] 内的素数，下标 0 起
int cnt;             // 素数个数

ll dp[MAXN];  // dp[j]：已处理的素数组中，选出的素数幂之和恰为 j 的方案数
ll nd[MAXN];  // 处理当前素数时的滚动数组：nd = 不选它 / 选它的某一个幂
int pw[MAXN]; // 当前素数在 [1, N] 内的所有幂 p, p^2, ... 共 k 个

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    // 埃氏筛出 [2, n] 的素数：每个素数是一个互斥物品组
    for (int i = 2; i <= n; i++) {
        if (notPrime[i]) continue;
        primes[cnt++] = i;
        for (int j = i + i; j <= n; j += i) notPrime[j] = true;
    }

    dp[0] = 1; // 一个素数都不选：幂和为 0，对应 lcm = 1（恒等置换，排数 2）

    for (int i = 0; i < cnt; i++) {
        int p = primes[i];
        int k = 0;
        for (ll q = p; q <= n; q *= p) pw[k++] = (int)q; // 该素数的全部合法幂

        for (int j = 0; j <= n; j++) nd[j] = dp[j]; // 先继承「不选素数 p」
        for (int j = 0; j <= n; j++) {
            if (dp[j] == 0) continue;
            for (int t = 0; t < k; t++) { // 同一素数至多选一个幂，故只看旧状态 dp
                int nj = j + pw[t];
                if (nj > n) break;
                nd[nj] += dp[j]; // 从旧状态转移，天然避免同组内多选
            }
        }
        for (int j = 0; j <= n; j++) dp[j] = nd[j];
    }

    ll ans = 0;
    for (int j = 0; j <= n; j++) ans += dp[j]; // 幂和 ≤ N 的所有选取都是合法 lcm
    printf("%lld\n", ans);

    return 0;
}
