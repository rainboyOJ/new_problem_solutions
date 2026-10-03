/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:07
 * update_at: 2026-10-02 15:07
 */
/*
 * 子任务解法：n <= 1e9（对应题面 70% 的评测用例）。
 *
 * 直接使用容斥公式 Q(n) = sum_{d=1}^{floor(sqrt(n))} mu(d) * floor(n / d^2)。
 * n <= 1e9 时 sqrt(n) <= 31623，线性筛出 mu 后直接枚举 d 即可，
 * 复杂度 O(sqrt(n))，和 main.cpp 的杜教筛路线相比只是少了「d 很大」这一段。
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXM = 40000;     // n <= 1e9 时 sqrt(n) <= 31623
static int mu[MAXM];
static int primes[MAXM];
static char isc[MAXM];
int pcnt;

int main() {
    ll n;
    scanf("%lld", &n);

    int N = (int)sqrtl((long double)n) + 1;
    if (N > MAXM - 1) N = MAXM - 1;

    // 线性筛莫比乌斯函数
    mu[1] = 1;
    for (int i = 2; i <= N; i++) {
        if (!isc[i]) {
            primes[++pcnt] = i;
            mu[i] = -1;
        }
        for (int j = 1; j <= pcnt; j++) {
            ll v = (ll)primes[j] * i;
            if (v > N) break;
            isc[v] = 1;
            if (i % primes[j] == 0) {
                mu[v] = 0;
                break;
            }
            mu[v] = -mu[i];
        }
    }

    // 直接枚举所有 d <= sqrt(n)
    ll ans = 0;
    for (ll d = 1; d <= N; d++) {
        ans += (ll)mu[d] * (n / (d * d));
    }

    printf("%lld\n", ans);
    return 0;
}
