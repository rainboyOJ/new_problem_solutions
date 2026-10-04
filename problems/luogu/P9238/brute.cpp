/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:07
 * update_at: 2026-10-02 15:07
 */
/*
 * brute.cpp：小数据暴力解，用来辅助对拍。
 *
 * 思路：完全不用莫比乌斯函数，直接按定义统计无平方因子数。
 * 对每个素数 p <= sqrt(n)，把 p^2 的所有倍数都标记成「含平方因子」，
 * 最后没被标记过的数就是无平方因子数，答案就是它们的个数。
 * 复杂度 O(n)，适合 n <= 2e7 的对拍规模。
 *
 * 它和 main.cpp 的莫比乌斯 + 杜教筛路线没有任何共享逻辑，
 * 是一个可以独立验证结论的暴力。
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20000005;
static char bad[MAXN];    // bad[x] = 1 表示 x 含平方因子
static int primes[1500000];
int pcnt;

int main() {
    int n;
    scanf("%d", &n);

    // 线性筛出 sqrt(n) 以内的素数
    int lim = (int)sqrt((double)n) + 1;
    vector<char> isc(lim + 1, 0);
    for (int i = 2; i <= lim; i++) {
        if (!isc[i]) primes[++pcnt] = i;
        for (int j = 1; j <= pcnt; j++) {
            long long v = (long long)primes[j] * i;
            if (v > lim) break;
            isc[(int)v] = 1;
            if (i % primes[j] == 0) break;
        }
    }

    // 把每个 p^2 的倍数标记为「含平方因子」
    for (int j = 1; j <= pcnt; j++) {
        long long sq = (long long)primes[j] * primes[j];
        for (long long x = sq; x <= n; x += sq) {
            bad[(int)x] = 1;
        }
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        if (!bad[i]) ans++;
    }

    printf("%lld\n", ans);
    return 0;
}
