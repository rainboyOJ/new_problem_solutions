/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-30 23:06
 * update_at: 2026-10-06 01:25
 */
#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;

typedef long long ll;

const int MAXP = 50000;       // 筛到 44722 足够覆盖 sqrt(2e9)
int primes[MAXP];             // 素数表
bool is_composite[MAXP];      // 筛法标记
int prime_cnt;                // 素数个数
ll divisors[2000];            // b1 的约数表（2e9 内约数最多约 1536 个）
int div_cnt;                  // 当前约数个数

// 预处理 [2, MAXP) 范围内的素数表（埃氏筛）
void init_primes() {
    for (int i = 2; i < MAXP; ++i) {
        if (!is_composite[i]) primes[++prime_cnt] = i;
        for (int j = 1; j <= prime_cnt && (ll)i * primes[j] < MAXP; ++j) {
            is_composite[i * primes[j]] = true;
            if (i % primes[j] == 0) break;
        }
    }
}

// 分解 n 的素因子，并通过笛卡尔积扩展出全部约数存入 divisors[]
void build_divisors(ll n) {
    div_cnt = 1;
    divisors[1] = 1;
    for (int i = 1; i <= prime_cnt && (ll)primes[i] * primes[i] <= n; ++i) {
        if (n % primes[i] != 0) continue;
        int e = 0;
        ll p = primes[i];
        while (n % p == 0) {
            n /= p;
            ++e;
        }
        // 把 p^0..p^e 乘进已有约数
        int old_cnt = div_cnt;
        ll pe = 1;
        for (int k = 1; k <= e; ++k) {
            pe *= p;
            for (int j = 1; j <= old_cnt; ++j) {
                divisors[++div_cnt] = divisors[j] * pe;
            }
        }
    }
    // 剩余部分为大于 sqrt(原n) 的素因子，指数为 1
    if (n > 1) {
        int old_cnt = div_cnt;
        for (int j = 1; j <= old_cnt; ++j) {
            divisors[++div_cnt] = divisors[j] * n;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_primes();

    int n;
    cin >> n;
    while (n--) {
        ll a0, a1, b0, b1;
        cin >> a0 >> a1 >> b0 >> b1;

        build_divisors(b1);

        int ans = 0;
        for (int i = 1; i <= div_cnt; ++i) {
            ll x = divisors[i];
            if (gcd(x, a0) == a1 && x / gcd(x, b0) * b0 == b1) {
                ++ans;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
