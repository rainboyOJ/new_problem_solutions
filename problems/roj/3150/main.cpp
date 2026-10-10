/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// naptime：断环成链后 DP，分「第 1 小时不续睡」与「第 1 小时续睡」两类互补求解。
#include <cstdio>
#include <vector>

typedef long long ll;

const ll NEG = -(1LL << 60); // 不可达状态

ll n, b;
std::vector<ll> awake, asleep, nxt_awake, nxt_asleep;

// 睡满 b 小时的最大恢复体力；wrapping 表示第 1 小时在续上一轮第 N 小时的觉
ll best_gain(std::vector<ll>& u, bool wrapping) {
    for (ll j = 0; j <= b; j++) {
        awake[j] = NEG;
        asleep[j] = NEG;
    }
    if (wrapping) {
        asleep[1] = u[0]; // 第 1 小时已睡熟，计入 U_1
    } else {
        awake[0] = 0;
        asleep[1] = 0; // 第 1 小时清醒，或刚入睡不计 U_1
    }
    if (b <= 0) return 0; // 题面保证 b ≥ 1，这里只做越界保护

    for (ll t = 1; t < n; t++) {
        ll gain = u[t];
        for (ll j = 0; j <= b; j++) {
            // 本小时清醒：体力不变
            nxt_awake[j] = (awake[j] > asleep[j]) ? awake[j] : asleep[j];
        }
        nxt_asleep[0] = NEG;
        for (ll j = 1; j <= b; j++) {
            ll ripe = asleep[j - 1] + gain; // 前一小时也睡着 → 睡熟了
            nxt_asleep[j] = (awake[j - 1] > ripe) ? awake[j - 1] : ripe;
        }
        for (ll j = 0; j <= b; j++) {
            awake[j] = nxt_awake[j];
            asleep[j] = nxt_asleep[j];
        }
    }

    if (wrapping) return asleep[b];
    return (awake[b] > asleep[b]) ? awake[b] : asleep[b];
}

int main() {
    if (scanf("%lld %lld", &n, &b) != 2) return 0; // 空输入安全返回
    std::vector<ll> u(n);
    for (ll i = 0; i < n; i++) scanf("%lld", &u[i]);

    awake.assign(b + 1, NEG);
    asleep.assign(b + 1, NEG);
    nxt_awake.assign(b + 1, NEG);
    nxt_asleep.assign(b + 1, NEG);

    ll a = best_gain(u, false);
    ll c = best_gain(u, true);
    printf("%lld\n", a > c ? a : c);
    return 0;
}
