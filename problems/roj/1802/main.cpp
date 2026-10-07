/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 04:05
 * update_at: 2026-10-08 04:05
 */
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

// 小质数表：n<=500 时 sqrt(500)≈22.36，不超过 22 的质数恰好是这 8 个
static const int SP[8] = {2, 3, 5, 7, 11, 13, 17, 19};
static const int ALL = 1 << 8; // 小质数掩码空间 256

struct Item {
    int bigp; // 去掉全部小质数后剩下的部分：1 表示「只含小质数」，>1 即该数唯一的大质因子
    int mask; // 小质数因子掩码，第 j 位表示含质数 SP[j]
};
static Item item[505];

// dp[x][y]：小 G 已用的小质因子集合为 x、小 W 为 y 的方案数（保证 x&y==0）
static ll dp[ALL][ALL];
static ll g1[ALL][ALL]; // 本组只能分给小 G 时的临时数组
static ll g2[ALL][ALL]; // 本组只能分给小 W 时的临时数组

static ll n, mod;
static int cnt;

bool cmpBigp(const Item &a, const Item &b) { return a.bigp < b.bigp; }

// 把一个数拆成「小质因子掩码」+「大质因子」，大质因子为 1 时不登记
void split(int x, int &mask, int &bigp) {
    mask = 0;
    for (int j = 0; j < 8; j++) {
        if (x % SP[j] == 0) {
            mask |= 1 << j;
            while (x % SP[j] == 0) x /= SP[j]; // 指数不影响互质性，除干净再找大质因子
        }
    }
    bigp = x;
}

// 把单个寿司 s 并入「只能给小 G」的 g1 数组：x 倒序保证同一个数不会被选两次
void pushG(ll f[ALL][ALL], int s) {
    for (int x = ALL - 1; x >= 0; x--) {
        for (int y = ALL - 1; y >= 0; y--) {
            ll v = f[x][y];
            if (v == 0) continue;
            if (s & y) continue; // 会与小 W 已有的质因子冲突，不能给小 G
            ll &t = f[x | s][y];
            t = (t + v) % mod;
        }
    }
}

// 对称地并入「只能给小 W」
void pushW(ll f[ALL][ALL], int s) {
    for (int x = ALL - 1; x >= 0; x--) {
        for (int y = ALL - 1; y >= 0; y--) {
            ll v = f[x][y];
            if (v == 0) continue;
            if (s & x) continue; // 会与小 G 已有的质因子冲突，不能给小 W
            ll &t = f[x][y | s];
            t = (t + v) % mod;
        }
    }
}

void solve() {
    if (scanf("%lld %lld", &n, &mod) != 2) return;
    if (mod <= 0) { // 题面数据表写作 0<=p，p=0 取模无定义，保底输出 0
        printf("0\n");
        return;
    }

    cnt = 0;
    for (int x = 2; x <= (int)n; x++) {
        int mask, bigp;
        split(x, mask, bigp);
        item[cnt].mask = mask;
        item[cnt].bigp = bigp;
        cnt++;
    }
    sort(item, item + cnt, cmpBigp); // 排序后同一大质因子的数连成一段

    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;

    int i = 0;
    while (i < cnt) {
        int j = i;
        while (j + 1 < cnt && item[j + 1].bigp == item[i].bigp) j++; // 当前组区间 [i, j]
        // 大质因子为 1 的数每个各自成一组（组内整组只能给一人，若不拆开就错）
        if (item[i].bigp == 1) j = i;

        memcpy(g1, dp, sizeof(dp));
        memcpy(g2, dp, sizeof(dp));
        for (int t = i; t <= j; t++) {
            // 同一大质因子的数互相不互质，整组只能给同一个人
            pushG(g1, item[t].mask);
            pushW(g2, item[t].mask);
        }
        for (int x = 0; x < ALL; x++) {
            for (int y = 0; y < ALL; y++) {
                // 「本组一个都不选」在 g1、g2 里各算了一次，容斥减去一个 dp
                ll v = (g1[x][y] + g2[x][y] - dp[x][y]) % mod;
                if (v < 0) v += mod;
                dp[x][y] = v;
            }
        }
        i = j + 1;
    }

    ll ans = 0;
    for (int x = 0; x < ALL; x++)
        for (int y = 0; y < ALL; y++)
            ans = (ans + dp[x][y]) % mod; // x&y!=0 的状态恒为 0，直接全加
    printf("%lld\n", ans);
}

int main() {
    solve();
    return 0;
}
