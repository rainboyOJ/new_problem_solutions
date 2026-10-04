/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 06:24
 * update_at: 2026-10-05 06:24
 */
// main.cpp：非降序列上二分找最接近每个询问值的元素。
#include <cstdio>

typedef long long ll;

const int MAXN = 100005;
ll a[MAXN]; // a[1..n] 保存非降序列

// 求 |u - v|
ll abs_diff(ll u, ll v) {
    ll d = u - v;
    if (d < 0) {
        d = -d;
    }
    return d;
}

int main() {
    ll n;
    if (scanf("%lld", &n) != 1) {
        return 0;
    }
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    ll m;
    scanf("%lld", &m);
    for (ll k = 1; k <= m; k++) {
        ll x;
        scanf("%lld", &x);

        // 二分收敛到相邻两点 left 与 right，它们夹住询问值 x
        ll left = 1;
        ll right = n;
        while (left < right - 1) {
            ll mid = (left + right) / 2;
            if (a[mid] > x) {
                right = mid;
            } else {
                left = mid;
            }
        }

        // 距离相等时取 a[left]，正好满足题面「多个值取最小」的要求
        if (abs_diff(a[left], x) <= abs_diff(a[right], x)) {
            printf("%lld\n", a[left]);
        } else {
            printf("%lld\n", a[right]);
        }
    }

    return 0;
}
