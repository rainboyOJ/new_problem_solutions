/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 小 Z 的袜子：莫队算法维护窗口内同色对数。
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

typedef long long ll;

const ll MAXN = 100005;

ll N, M;
ll a[MAXN];
ll cnt[MAXN]; // cnt[c]：当前窗口里颜色 c 的只数
ll cur = 0;   // 当前窗口内同色袜子对数 C(c,2) 之和
ll mo_size;

struct Query {
    ll l, r, id;
};

Query qs[MAXN];
ll ans_num[MAXN], ans_den[MAXN];

// 右端点加入第 i 只袜子，登记它与窗口内同色袜子配成的新对
void expand(ll i) {
    ll c = a[i];
    cur += cnt[c];
    cnt[c]++;
}

// 左端点移出第 i 只袜子，撤销它贡献的同色对
void shrink(ll i) {
    ll c = a[i];
    cnt[c]--;
    cur -= cnt[c];
}

ll block_less(const Query& x, const Query& y) {
    ll bx = x.l / mo_size, by = y.l / mo_size;
    if (bx != by) return bx < by;
    return (bx % 2 == 0) ? (x.r < y.r) : (x.r > y.r);
}

ll gcd2(ll x, ll y) {
    while (y) {
        ll t = x % y;
        x = y;
        y = t;
    }
    return x;
}

ll isqrt_ll(ll v) {
    if (v <= 0) return 0;
    ll r = (ll)std::sqrt((double)v);
    while (r > 0 && r * r > v) r--;
    while ((r + 1) * (r + 1) <= v) r++;
    return r;
}

int main() {
    if (scanf("%lld %lld", &N, &M) != 2) return 0; // 空输入安全返回
    ll maxc = 0;
    for (ll i = 0; i < N; i++) {
        scanf("%lld", &a[i]);
        if (a[i] > maxc) maxc = a[i];
    }
    for (ll i = 0; i <= maxc && i < MAXN; i++) cnt[i] = 0;

    for (ll i = 0; i < M; i++) {
        scanf("%lld %lld", &qs[i].l, &qs[i].r);
        qs[i].l--;
        qs[i].r--;
        qs[i].id = i;
    }

    mo_size = N / (M > 0 ? (isqrt_ll(M) > 0 ? isqrt_ll(M) : 1) : 1);
    if (mo_size < 1) mo_size = 1;
    std::sort(qs, qs + M, block_less);

    ll cur_l = 0, cur_r = -1; // 空窗口用 cur_r < cur_l 表示
    for (ll t = 0; t < M; t++) {
        ll l = qs[t].l, r = qs[t].r, id = qs[t].id;
        while (cur_l > l) {
            cur_l--;
            expand(cur_l);
        }
        while (cur_r < r) {
            cur_r++;
            expand(cur_r);
        }
        while (cur_l < l) {
            shrink(cur_l);
            cur_l++;
        }
        while (cur_r > r) {
            shrink(cur_r);
            cur_r--;
        }
        ll total = (r - l + 1) * (r - l) / 2;
        ll same = cur;
        if (same == 0) {
            ans_num[id] = 0;
            ans_den[id] = 1;
        } else {
            ll g = gcd2(same, total);
            ans_num[id] = same / g;
            ans_den[id] = total / g;
        }
    }

    for (ll i = 0; i < M; i++) {
        printf("%lld/%lld\n", ans_num[i], ans_den[i]);
    }
    return 0;
}
