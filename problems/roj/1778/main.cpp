/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 02:12
 * update_at: 2026-10-08 02:12
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MOD = 999983;      // 题目要求的取模值
const int MAXN = 1000;       // n 的上限
const int MAXS = 9 * MAXN + 1; // 各位数字和的上限：最多 n 位、每位最大 9

// f[s] = 用 S 中数字构成 k 位数、各位数字和恰为 s 的方案数（mod MOD）
// 滚动推进 k：cur 是 f[k]，nxt 是 f[k+1]。值域 < 999983 < 2^20，int 够用
int cur[MAXS];
int nxt[MAXS];

int fn[MAXS];  // 快照 f[n][*]
int f1[MAXS];  // 快照 f[l1][*]，l1 = ceil(n/2)
int f2[MAXS];  // 快照 f[l2][*]，l2 = floor(n/2)

int dig[16];   // 集合 S 里的数字（已去重，按输入顺序）
int digCnt;    // |S|

// 返回 sum_s f[s]^2 mod MOD：即「两段各 k 位、数字和相等的方案数」
ll square_sum(const int* f, int lim) {
    ll res = 0;
    for (int s = 0; s <= lim; s++) {
        res = (res + (ll)f[s] * f[s]) % MOD;
    }
    return res;
}

int main() {
    ll n;
    if (scanf("%lld", &n) != 1) return 0;

    char str[64];
    if (scanf("%63s", str) != 1) return 0;

    // 集合去重：题面给的是「数字集合」，重复字符只算一个数字
    bool used[10] = {false};
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        int d = str[i] - '0';
        if (!used[d]) {
            used[d] = true;
            dig[digCnt++] = d;
        }
    }

    // 前 n 位里奇数位有 l1 个、偶数位有 l2 个（n 为奇数时 l1 = l2 + 1）
    ll l1 = (n + 1) / 2;
    ll l2 = n / 2;

    memset(cur, 0, sizeof(cur));
    cur[0] = 1;  // f[0][0] = 1：0 位、和为 0 的方案数为 1

    // 规模为 0 的快照（n = 1 时 l2 = 0 会用到）
    if (l2 == 0) memcpy(f2, cur, sizeof(f2));
    if (l1 == 0) memcpy(f1, cur, sizeof(f1));

    // 背包计数：每加一位，就枚举集合里的数字做一次转移
    for (ll k = 1; k <= n; k++) {
        int lim = 9 * (int)k;      // k 位的数字和不会超过 9k
        memset(nxt, 0, sizeof(int) * (lim + 1));
        for (int s = 0; s <= lim; s++) {
            ll acc = 0;
            for (int j = 0; j < digCnt; j++) {
                int d = dig[j];
                if (s - d >= 0) acc += cur[s - d];
            }
            nxt[s] = (int)(acc % MOD);
        }
        memcpy(cur, nxt, sizeof(int) * (lim + 1));  // 滚动到第 k 位
        if (k == l1) memcpy(f1, cur, sizeof(f1));
        if (k == l2) memcpy(f2, cur, sizeof(f2));
        if (k == n)  memcpy(fn, cur, sizeof(fn));
    }

    // 前 n 位之和 = 后 n 位之和的方案数，与奇数位之和 = 偶数位之和的方案数同为 A
    ll A = square_sum(fn, 9 * (int)n);
    // 交集：s1 = s4 且 s2 = s3，两组位置各自独立，方案数相乘
    ll inter = square_sum(f1, 9 * (int)l1) * square_sum(f2, 9 * (int)l2) % MOD;

    ll ans = (2 * A % MOD - inter % MOD + MOD) % MOD;
    printf("%lld\n", ans);
    return 0;
}
