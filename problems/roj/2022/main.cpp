/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:40
 * update_at: 2026-10-06 09:40
 */
// main.cpp：枚举分母不超过 N 的分数，gcd 约分去重后按分数值升序输出。
#include <cstdio>
#include <set>
#include <vector>
#include <algorithm>

typedef long long ll;

std::set<std::pair<ll, ll> > unique_frac;  // 约分后的 (分子, 分母) 集合，天然去重
std::vector<std::pair<ll, ll> > fractions; // 去重后的最简分数，排序后输出

// 求 x 与 y 的最大公约数，用于把 a/b 约成最简分数。
ll gcd_ll(ll x, ll y) {
    while (y != 0) {
        ll temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

// 比较函数：a/b < c/d 等价于 a*d < c*b，用交叉相乘避免浮点误差。
bool frac_less(std::pair<ll, ll> x, std::pair<ll, ll> y) {
    return x.first * y.second < y.first * x.second;
}

int main() {
    ll n;
    std::scanf("%lld", &n);

    // 枚举 b 从 1 到 n、a 从 0 到 b，把每个分数约分后丢进集合去重。
    ll b, a;
    for (b = 1; b <= n; b++) {
        for (a = 0; a <= b; a++) {
            ll g = gcd_ll(a, b);
            unique_frac.insert(std::make_pair(a / g, b / g));
        }
    }

    for (std::set<std::pair<ll, ll> >::iterator it = unique_frac.begin(); it != unique_frac.end(); ++it) {
        fractions.push_back(*it);
    }
    std::sort(fractions.begin(), fractions.end(), frac_less);

    for (std::vector<std::pair<ll, ll> >::iterator it = fractions.begin(); it != fractions.end(); ++it) {
        std::printf("%lld/%lld\n", it->first, it->second);
    }
    return 0;
}
