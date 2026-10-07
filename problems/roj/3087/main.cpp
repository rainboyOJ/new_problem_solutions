/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:11
 * update_at: 2026-10-06 18:11
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll SIEVE_LIMIT = 44721;    // 只需筛出 sqrt(2·10^9) 以内的质数，用于分解 a0 与 b1
const ll UNBOUNDED = 1000000000; // 指数只被单侧限制时的上界哨兵，任何真实指数都远小于它

ll n;
ll a0, a1, b0, b1;

char not_prime[SIEVE_LIMIT + 5]; // 埃氏筛标记：1 表示合数
ll primes[5000];                 // 筛出的质数，sqrt(2·10^9) 以内共有 4648 个
ll prime_cnt;                    // primes[1..prime_cnt] 有效

// 筛出试除分解所需的质数表。
void build_primes() {
    for (ll i = 2; i <= SIEVE_LIMIT; i++) {
        if (not_prime[i]) continue;
        primes[++prime_cnt] = i;
        for (ll j = i * i; j <= SIEVE_LIMIT; j += i) {
            not_prime[j] = 1;
        }
    }
}

// 固定一个质数 p 后，合法指数 e = v_p(x) 的取值个数。
// 参数依次是 v_p(a0)、v_p(a1)、v_p(b0)、v_p(b1) 的指数值。
// 条件 min(e, a) = a1 与 max(e, b0) = b1 各自把 e 限制成「一个定值」或「一段区间」，
// 取交集后数区间内的整数个数；交集为空返回 0，整题答案随之变成 0。
ll exponent_count(ll exp_a, ll exp_a1, ll exp_b0, ll exp_b1) {
    ll low1, high1;
    if (exp_a1 < exp_a) {
        low1 = exp_a1;
        high1 = exp_a1; // a1 < a 时条件 1 逼出唯一定值 e = a1
    } else {
        low1 = exp_a1;
        high1 = UNBOUNDED; // a1 = a 时条件 1 等价于下界 e >= a1
    }

    ll low2, high2;
    if (exp_b0 < exp_b1) {
        low2 = exp_b1;
        high2 = exp_b1; // b0 < b1 时条件 2 逼出唯一定值 e = b1
    } else {
        low2 = 0;
        high2 = exp_b1; // b0 = b1 时条件 2 等价于上界 e <= b1
    }

    ll low = max(low1, low2);
    ll high = min(high1, high2);
    if (high < low) return 0;
    return high - low + 1;
}

void solve() {
    cin >> n;
    for (ll query = 1; query <= n; query++) {
        cin >> a0 >> a1 >> b0 >> b1;

        ll rest_a0 = a0, rest_a1 = a1, rest_b0 = b0, rest_b1 = b1;
        ll ans = 1;

        // 逐质数处理：只关心整除 a0 或 b1 的质数，其余位上四个指数都是 0，方案数固定为 1。
        // a1 | a0、b0 | b1，所以两个数各自边除边缩小，不影响条件对应的指数关系。
        for (ll i = 1; i <= prime_cnt; i++) {
            ll p = primes[i];
            if (p * p > max(rest_a0, rest_b1)) break; // 剩下的部分已不可能含两个以上该质数因子
            if (rest_a0 % p != 0 && rest_b1 % p != 0) continue;

            ll exp_a0 = 0, exp_a1 = 0, exp_b0 = 0, exp_b1 = 0;
            while (rest_a0 % p == 0) {
                rest_a0 /= p;
                exp_a0++;
            }
            while (rest_a1 % p == 0) {
                rest_a1 /= p;
                exp_a1++;
            }
            while (rest_b0 % p == 0) {
                rest_b0 /= p;
                exp_b0++;
            }
            while (rest_b1 % p == 0) {
                rest_b1 /= p;
                exp_b1++;
            }
            ans *= exponent_count(exp_a0, exp_a1, exp_b0, exp_b1);
        }

        // 试除结束后四段剩余都是 1 或一个大质数（指数只能取 0 或 1），逐个当作新质数收尾。
        ll remainder[4] = {rest_a0, rest_a1, rest_b0, rest_b1};
        for (ll i = 0; i < 4; i++) {
            ll q = remainder[i];
            if (q == 1) continue;

            bool repeated = false; // 同一个大质数只处理一次
            for (ll j = 0; j < i; j++) {
                if (remainder[j] == q) {
                    repeated = true;
                    break;
                }
            }
            if (repeated) continue;

            ll exp_a0 = (rest_a0 % q == 0) ? 1 : 0;
            ll exp_a1 = (rest_a1 % q == 0) ? 1 : 0;
            ll exp_b0 = (rest_b0 % q == 0) ? 1 : 0;
            ll exp_b1 = (rest_b1 % q == 0) ? 1 : 0;
            ans *= exponent_count(exp_a0, exp_a1, exp_b0, exp_b1);
        }

        cout << ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build_primes();
    solve();

    return 0;
}
