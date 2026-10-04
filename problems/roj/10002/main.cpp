/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 21:53
 * update_at: 2026-10-04 21:53
 */

#include <cstdio>
#include <cmath>
#include <map>
#include <set>
#include <vector>
#include <iostream>

using namespace std;

typedef long long ll;

const int MAXP = 1260;          // 只需试除到 1259

vector<int> primes;             // 1260 以内的素数表

// 一个数的立方核与其互补核
struct Core {
    ll f;                       // 立方核：剥掉所有立方因子后剩下的部分
    ll g;                       // 互补核：与 f 相乘得到完全立方数的唯一立方核
};

// 筛出 2..1259 的所有素数
void init_primes() {
    static bool vis[MAXP];
    for (int i = 2; i < MAXP; i++) {
        if (!vis[i]) {
            primes.push_back(i);
            if ((ll)i * i < MAXP) {
                for (int j = i * i; j < MAXP; j += i) vis[j] = true;
            }
        }
    }
}

// 对 x 做质因数分解，去掉所有立方因子得到立方核 f，并算出互补核 g
Core reduce(ll x) {
    ll f = 1, g = 1;
    for (int i = 0; i < (int)primes.size(); i++) {
        int p = primes[i];
        if ((ll)p * p > x) break;            // 更小的素数都已除尽，x 剩余部分为 1 或大于 p 的素数
        if (x % p != 0) continue;
        int e = 0;
        while (x % p == 0) {
            x /= p;
            e++;
        }
        int r = e % 3;
        if (r == 1) {                        // 指数模 3 余 1：核留 p，补需要 p^2
            f *= p;
            g *= (ll)p * p;
        } else if (r == 2) {                 // 指数模 3 余 2：核留 p^2，补需要 p
            f *= (ll)p * p;
            g *= p;
        }
    }
    // 剩余部分所有素因子都大于 1259，只可能是 1、p、p^2 或 p*q
    if (x > 1) {
        ll s = sqrt((long double)x);
        while ((s + 1) * (s + 1) <= x) s++;
        while (s * s > x) s--;
        if (s * s == x) {                    // x = p^2，核指数取 2，补需要 p
            f *= x;
            g *= s;
        } else {                             // x = p 或 p*q，所有素因子指数均为 1
            f *= x;
            __int128 t = (__int128)g * x * x;
            g = (ll)t;
        }
    }
    return (Core){f, g};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    init_primes();

    int n;
    if (!(cin >> n)) return 0;

    map<ll, int> cnt;            // 每个立方核出现的次数
    for (int i = 0; i < n; i++) {
        ll a;
        cin >> a;
        cnt[reduce(a).f]++;
    }

    ll ans = 0;
    set<ll> taken;               // 已经结算过的核，避免互补对重复计算
    for (map<ll, int>::iterator it = cnt.begin(); it != cnt.end(); ++it) {
        ll core = it->first;
        int c = it->second;
        if (taken.count(core)) continue;

        if (core == 1) {         // 核为 1 的数两两冲突，最多留 1 个
            ans += 1;
            taken.insert(1);
            continue;
        }

        ll other = reduce(core).g;          // core 的互补核
        int c2 = 0;
        map<ll, int>::iterator jt = cnt.find(other);
        if (jt != cnt.end()) c2 = jt->second;

        ans += max(c, c2);                  // 每对互补核取人数较多的一侧
        taken.insert(core);
        taken.insert(other);
    }

    cout << ans << "\n";
    return 0;
}
