/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// GSS：线段树维护 sum / pre / suf / best 四元组，迭代式建树、查询与单点修改。
#include <cstdio>

typedef long long ll;

const ll MAXB = 1 << 19; // 叶子层长度上限（n ≤ 5e5）
const ll NEG = -(1LL << 60); // 空区间的最大子段和

struct Node {
    ll sum;  // 区间和
    ll pre;  // 最大前缀和
    ll suf;  // 最大后缀和
    ll best; // 最大子段和
};

Node t[2 * MAXB];
ll base; // 叶子层长度（≥ n 的最小 2 的幂）

// 由左右孩子重算 p 的四个量
void pull(ll p) {
    ll a = p << 1;
    ll s1 = t[a].sum, p1 = t[a].pre, u1 = t[a].suf, b1 = t[a].best;
    ll s2 = t[a + 1].sum, p2 = t[a + 1].pre, u2 = t[a + 1].suf, b2 = t[a + 1].best;
    t[p].sum = s1 + s2;
    ll x = s1 + p2;
    t[p].pre = p1 > x ? p1 : x; // pre = max(左 pre, 左 sum + 右 pre)
    x = s2 + u1;
    t[p].suf = u2 > x ? u2 : x; // suf = max(右 suf, 右 sum + 左 suf)
    ll b = b1 > b2 ? b1 : b2;
    x = u1 + p2;
    t[p].best = b > x ? b : x; // best = max(左 best, 右 best, 左 suf + 右 pre)
}

// 区间最大连续子段和：把 [l, r) 拆成若干节点，分左右两段归并
ll query(ll l, ll r) {
    l += base;
    r += base;
    ll ls = 0; // 左暂存区的 sum，按「空区间」起步
    ll lp = NEG, lu = NEG, lb = NEG, rp = NEG, rb = NEG;
    while (l < r) {
        if (l & 1) {
            ll u = lu; // 先存旧 suf：合并式里必须用归属左段的旧值
            ll x = ls + t[l].pre;
            lp = lp > x ? lp : x;
            x = t[l].sum + u;
            lu = t[l].suf > x ? t[l].suf : x;
            x = u + t[l].pre;
            ll b = lb > t[l].best ? lb : t[l].best;
            lb = b > x ? b : x;
            ls += t[l].sum;
            l++;
        }
        if (r & 1) {
            r--;
            ll p = rp; // 同理，先存旧 pre
            ll x = t[r].sum + p;
            rp = t[r].pre > x ? t[r].pre : x;
            x = t[r].suf + p;
            ll b = rb > t[r].best ? rb : t[r].best;
            rb = b > x ? b : x;
        }
        l >>= 1;
        r >>= 1;
    }
    ll b = lb > rb ? lb : rb; // 左暂存区在右、右暂存区在左，只有跨界的 lu+rp 相连
    ll x = lu + rp;
    return b > x ? b : x;
}

// 单点修改：改写叶子，再沿父链逐层重新合并
void update(ll i, ll v) {
    ll c = base + i;
    t[c].sum = t[c].pre = t[c].suf = t[c].best = v;
    c >>= 1;
    while (c) {
        pull(c);
        c >>= 1;
    }
}

int main() {
    ll n, m;
    if (scanf("%lld %lld", &n, &m) != 2) return 0; // 空输入安全返回

    base = 1;
    while (base < n) {
        base <<= 1;
    }

    for (ll i = 0; i < n; i++) {
        ll v;
        scanf("%lld", &v);
        t[base + i].sum = t[base + i].pre = t[base + i].suf = t[base + i].best = v;
    }
    // 补位叶子仍是 0，但它所在的整块区间都超出 [0, n)，查询永远选不到
    for (ll p = base - 1; p >= 1; p--) {
        pull(p);
    }

    for (ll q = 0; q < m; q++) {
        ll k, x, y;
        scanf("%lld %lld %lld", &k, &x, &y);
        if (k == 1) {
            if (x > y) {
                ll tmp = x;
                x = y;
                y = tmp;
            }
            printf("%lld\n", query(x - 1, y));
        } else {
            update(x - 1, y);
        }
    }
    return 0;
}
