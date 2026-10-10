/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 硬币组合：多重背包二进制拆分，用位图整体左移表示「面值和能否拼成」。
#include <cstdio>
#include <vector>

typedef long long ll;

const int MAXM = 100005;
unsigned long long W64[(MAXM + 64) / 64 + 16];
int nw;

// reach |= reach << s，然后把超出 m 的位清掉
void shift_or(ll s, ll m) {
    ll ws = s >> 6, bs = s & 63;
    if (bs == 0) {
        for (int i = nw - 1; i >= (int)ws; i--) W64[i] |= W64[i - ws];
    } else {
        for (int i = nw - 1; i > (int)ws; i--) {
            W64[i] |= (W64[i - ws] << bs) | (W64[i - ws - 1] >> (64 - bs));
        }
        W64[ws] |= W64[0] << bs;
    }
    int lastbit = (int)(m >> 6);
    int rem = (int)(m & 63);
    W64[lastbit] &= (rem == 63) ? ~0ULL : ((1ULL << (rem + 1)) - 1);
    for (int i = lastbit + 1; i < nw; i++) W64[i] = 0;
}

int main() {
    ll n, m;
    while (scanf("%lld %lld", &n, &m) == 2) {
        if (n == 0 && m == 0) break; // 终止用例，不产生输出
        std::vector<ll> values(n), counts(n);
        for (ll i = 0; i < n; i++) scanf("%lld", &values[i]);
        for (ll i = 0; i < n; i++) scanf("%lld", &counts[i]);

        nw = (int)((m + 1 + 63) / 64) + 2;
        for (int i = 0; i < nw; i++) W64[i] = 0;
        W64[0] = 1; // 第 0 位 = 空集

        for (ll i = 0; i < n; i++) {
            ll count = counts[i];
            ll size = 1;
            while (count) {
                ll take = size < count ? size : count; // 最后一组可能不满
                ll shift = values[i] * take;
                if (shift <= m) { // 位移超过 m 的组只会落到 m 之外
                    shift_or(shift, m);
                }
                count -= take;
                size <<= 1;
            }
        }

        ll total = 0;
        for (int i = 0; i < nw; i++) total += __builtin_popcountll(W64[i]);
        printf("%lld\n", total - 1); // 去掉第 0 位的空集
    }
    return 0;
}
