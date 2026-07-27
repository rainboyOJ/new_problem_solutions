/**
 * P1835 素数密度
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXV = 50000; // sqrt(2^31) ≈ 46340
const int MAXL = 1000005;

bool is_prime[MAXV + 5]; // 小范围内筛素数
int primes[MAXV], pcnt;
bool seg[MAXL]; // 区间 [l,r] 的素数标记

int main() {
    int l, r;
    scanf("%d%d", &l, &r);
    // 小范围素数筛
    memset(is_prime, 1, sizeof(is_prime));
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= MAXV; ++i) {
        if (is_prime[i]) {
            primes[++pcnt] = i;
            if ((long long)i * i <= MAXV) {
                for (int j = i * i; j <= MAXV; j += i)
                    is_prime[j] = false;
            }
        }
    }
    // 大区间筛
    for (int i = 1; i <= pcnt; ++i) {
        int p = primes[i];
        long long start = max(1LL * p * p, (l + p - 1LL) / p * p);
        for (long long j = start; j <= r; j += p)
            seg[j - l] = true;
    }
    if (l == 1) seg[0] = true;
    int ans = 0;
    for (int i = 0; i <= r - l; ++i)
        if (!seg[i]) ++ans;
    printf("%d\n", ans);
    return 0;
}
