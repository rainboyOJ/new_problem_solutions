/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 区间加 + 区间 gcd：差分后区间 gcd 变成单点改 + 区间 gcd，配 zkw 线段树与树状数组。
#include <cstdio>
#include <string>

typedef long long ll;

const ll MAXN = 500005;
const ll MAXSEG = 1 << 19;

ll n, m;
ll a[MAXN];
ll b[MAXN];             // 差分 b[i] = a[i] - a[i-1]
ll tree[2 * MAXSEG];    // zkw 线段树：叶子是 b[i]，内部节点是子树 gcd
ll bit[MAXN];           // 树状数组维护 b 的前缀和
ll size;                // 叶子层长度

ll gcd2(ll x, ll y) {
    if (x < 0) x = -x; // 与 Python 的 math.gcd 一致：结果恒为非负
    if (y < 0) y = -y;
    while (y) {
        ll t = x % y;
        x = y;
        y = t;
    }
    return x;
}

// 差分点 b[p] += d，同步更新线段树与树状数组
void update(ll p, ll d) {
    ll i = size + p - 1;
    tree[i] += d;
    while (i > 1) { // 只有到根的一条链会变化
        i >>= 1;
        tree[i] = gcd2(tree[2 * i], tree[2 * i + 1]);
    }
    i = p;
    while (i <= n) {
        bit[i] += d;
        i += i & -i;
    }
}

// 差分 b[l..r]（1-based）的 gcd
ll range_gcd(ll l, ll r) {
    ll res = 0;
    ll lo = size + l - 1, hi = size + r;
    while (lo < hi) {
        if (lo & 1) {
            res = gcd2(res, tree[lo]);
            lo++;
        }
        if (hi & 1) {
            hi--;
            res = gcd2(res, tree[hi]);
        }
        lo >>= 1;
        hi >>= 1;
    }
    return res;
}

int main() {
    if (scanf("%lld %lld", &n, &m) != 2) return 0; // 空输入安全返回
    for (ll i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    for (ll i = 1; i <= n; i++) {
        b[i] = a[i] - a[i - 1]; // 区间加 [l,r] 变成 b[l] += d、b[r+1] -= d
    }

    ll log = 1;
    while ((1LL << log) < n) {
        log++;
    }
    if (n <= 1) {
        log = 1;
    }
    size = 1LL << log;
    for (ll i = 1; i <= n; i++) {
        tree[size + i - 1] = b[i];
    }
    for (ll i = size - 1; i >= 1; i--) {
        tree[i] = gcd2(tree[2 * i], tree[2 * i + 1]);
    }

    // 树状数组 O(n) 建树
    for (ll i = 1; i <= n; i++) {
        bit[i] += b[i];
        ll j = i + (i & -i);
        if (j <= n) {
            bit[j] += bit[i];
        }
    }

    for (ll q = 0; q < m; q++) {
        char op[4];
        ll l, r;
        scanf("%s %lld %lld", op, &l, &r);
        if (op[0] == 'C') {
            ll d;
            scanf("%lld", &d);
            update(l, d);
            if (r < n) {
                update(r + 1, -d);
            }
        } else {
            // gcd(a[l..r]) = gcd(a[l], b[l+1..r])，a[l] 用前缀和求出
            ll s = 0, i = l;
            while (i) {
                s += bit[i];
                i -= i & -i;
            }
            ll res = s < 0 ? -s : s;
            if (l < r) {
                res = gcd2(res, range_gcd(l + 1, r));
            }
            printf("%lld\n", res);
        }
    }
    return 0;
}
