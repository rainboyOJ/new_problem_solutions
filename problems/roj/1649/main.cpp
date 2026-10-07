/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:26
 * update_at: 2026-10-06 00:26
 */
// main.cpp：「一本通 6.6 例 2」2^k 进制数
// 思路：按位数 n 分类，kn <= w 的档整档用组合数 C(m-1, n) 求和；
// 临界档（k(n-1) < w < kn）只卡首位 d1 < 2^t（t = w - k(n-1)），
// 贡献为 sum C(m-1-d1, n-1)；k(n-1) >= w 的档全超长，直接截断。
// 结果可达 200 位十进制，用 10^9 进制的大整数数组实现。

#include <cstdio>
#include <algorithm>
typedef long long ll;
using namespace std;

const ll BASE = 1000000000LL; // 大整数用 10^9 进制压位
const int MAXL = 30;          // 结果不超过 200 位十进制，30 段足够

// 全局大整数：ans 存最终答案，tmp 存每次算出的组合数（低位在前）
ll ans[MAXL];
ll tmp[MAXL];
int anslen;
int tmplen;

// 清零大整数
void big_zero(ll a[], int &len) {
    len = 1;
    a[0] = 0;
}

// ans += tmp，逐段相加处理进位
void big_add() {
    int l = max(anslen, tmplen);
    ll carry = 0;
    for (int i = 0; i < l; i++) {
        ll s = carry;
        if (i < anslen) s += ans[i];
        if (i < tmplen) s += tmp[i];
        ans[i] = s % BASE;
        carry = s / BASE;
    }
    anslen = l;
    while (carry > 0) {
        ans[anslen++] = carry % BASE;
        carry /= BASE;
    }
}

// tmp *= x（x 为小整数），逐段乘加进位
void big_mul(ll x) {
    ll carry = 0;
    for (int i = 0; i < tmplen; i++) {
        ll s = tmp[i] * x + carry;
        tmp[i] = s % BASE;
        carry = s / BASE;
    }
    while (carry > 0) {
        tmp[tmplen++] = carry % BASE;
        carry /= BASE;
    }
}

// tmp /= x（x 为小整数），高位到低位做除法
void big_div(ll x) {
    ll rem = 0;
    for (int i = tmplen - 1; i >= 0; i--) {
        ll cur = rem * BASE + tmp[i];
        tmp[i] = cur / x;
        rem = cur % x;
    }
    while (tmplen > 1 && tmp[tmplen - 1] == 0) tmplen--;
}

// 把组合数 C(N, K) 算进 tmp；利用前缀积 C(N,i) 都是整数，边乘边除不会失精度
void big_comb(ll N, ll K) {
    big_zero(tmp, tmplen);
    tmp[0] = 1;
    for (ll i = 1; i <= K; i++) {
        big_mul(N - K + i);
        big_div(i);
    }
}

int main() {
    ll k, w;
    scanf("%lld %lld", &k, &w);
    ll m = 1LL << k; // 2^k 进制，数位集合 {0,1,...,m-1}

    big_zero(ans, anslen);
    for (ll n = 2; n <= m - 1; n++) { // 位数 n：至少 2 位，至多 m-1 位
        if (k * (n - 1) >= w) break;  // r >= 2^{k(n-1)} >= 2^w，再长全超长，截断
        if (k * n <= w) {
            // 全合法档：r < 2^{kn} <= 2^w，选 n 个递增数位即唯一确定一个 r
            big_comb(m - 1, n);
            big_add();
        } else {
            // 临界档：条件 3 恰等价于首位 d1 < 2^t，t = w - k(n-1)
            ll t = w - k * (n - 1);
            ll top = 1LL << t;
            for (ll d1 = 1; d1 <= top - 1; d1++) { // 首位非 0 且小于 2^t
                ll N = m - 1 - d1; // 余下 n-1 位从 d1+1..m-1 里选
                if (N < n - 1) continue; // 候选数位不够，组合数为 0
                big_comb(N, n - 1);
                big_add();
            }
        }
    }

    // 输出：最高段不带前导 0，其余段补足 9 位
    printf("%lld", ans[anslen - 1]);
    for (int i = anslen - 2; i >= 0; i--) printf("%09lld", ans[i]);
    printf("\n");
    return 0;
}
