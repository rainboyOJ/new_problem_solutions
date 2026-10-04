/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:44
 * update_at: 2026-10-05 07:44
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

ll n, mod;
ll a[MAXN];             // 初始数列 a[1..n]
ll sumv[MAXN << 2];     // 线段树节点维护的区间和（恒小于 mod）
ll mulv[MAXN << 2];     // 懒标记的乘分量：孩子还欠着的变换是 x -> mulv*x
ll addv[MAXN << 2];     // 懒标记的加分量：孩子还欠着的变换是 x -> mulv*x+addv

// 把仿射变换 x -> b*x+c 整段作用到节点 node（对应区间长度 ln）。
// 原标记 (mulv, addv) 表示先做它再做新变换，复合为 (mulv*b, addv*b+c)。
void apply_node(ll node, ll ln, ll b, ll c) {
    sumv[node] = (b * sumv[node] + c * ln) % mod;
    mulv[node] = mulv[node] * b % mod;
    addv[node] = (addv[node] * b + c) % mod;
}

// 把节点 node 的懒标记下推给孩子，随后本节点标记复位为恒等变换 (1, 0)。
// 只有未被操作区间整段覆盖时才会下推，此时必有 lo < hi，两个孩子一定存在。
void push_down(ll node, ll lo, ll hi) {
    if (mulv[node] == 1 && addv[node] == 0) return;
    ll mid = (lo + hi) >> 1;
    apply_node(node << 1, mid - lo + 1, mulv[node], addv[node]);
    apply_node(node << 1 | 1, hi - mid, mulv[node], addv[node]);
    mulv[node] = 1;
    addv[node] = 0;
}

// 建树：叶子存单个数，父节点存两个孩子和再对 mod 取模。
void build(ll node, ll lo, ll hi) {
    mulv[node] = 1;
    addv[node] = 0;
    if (lo == hi) {
        sumv[node] = a[lo] % mod;
        return;
    }
    ll mid = (lo + hi) >> 1;
    build(node << 1, lo, mid);
    build(node << 1 | 1, mid + 1, hi);
    sumv[node] = (sumv[node << 1] + sumv[node << 1 | 1]) % mod;
}

// 区间 [ql, qr] 整段套用变换 x -> b*x+c。
void update(ll node, ll lo, ll hi, ll ql, ll qr, ll b, ll c) {
    if (ql <= lo && hi <= qr) {
        apply_node(node, hi - lo + 1, b, c);
        return;
    }
    push_down(node, lo, hi);
    ll mid = (lo + hi) >> 1;
    if (ql <= mid) update(node << 1, lo, mid, ql, qr, b, c);
    if (qr > mid) update(node << 1 | 1, mid + 1, hi, ql, qr, b, c);
    sumv[node] = (sumv[node << 1] + sumv[node << 1 | 1]) % mod;
}

// 查询区间 [ql, qr] 的和模 mod。
ll query(ll node, ll lo, ll hi, ll ql, ll qr) {
    if (ql <= lo && hi <= qr) return sumv[node];
    push_down(node, lo, hi);
    ll mid = (lo + hi) >> 1;
    ll total = 0;
    if (ql <= mid) total = query(node << 1, lo, mid, ql, qr);
    if (qr > mid) total += query(node << 1 | 1, mid + 1, hi, ql, qr);
    return total % mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> mod;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }
    build(1, 1, n);

    ll m;
    cin >> m;
    for (ll i = 1; i <= m; i++) {
        ll op, l, r, c;
        cin >> op >> l >> r;
        if (op == 3) {
            cout << query(1, 1, n, l, r) << "\n";
            continue;
        }
        cin >> c;
        c %= mod;
        // 操作 1 是变换 x -> c*x；操作 2 是变换 x -> x+c。
        if (op == 1) {
            update(1, 1, n, l, r, c, 0);
        } else {
            update(1, 1, n, l, r, 1, c);
        }
    }

    return 0;
}
