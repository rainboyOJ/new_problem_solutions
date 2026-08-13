/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 08:46
 * update_at: 2026-08-13 08:46
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

ll a[MAXN]; // 初始数列

// 仿照 rbook 模板 segtree-range-assign 的 pull/apply/push 结构，
// 懒标记从「区间赋值」改成「待加等差数列」。
struct SegmentTreeAP {
    int n = 0;
    vector<ll> sum;   // sum[p]：节点 p 区间的和
    vector<ll> first; // 懒标记：该区间最左端位置待加的值
    vector<ll> diff;  // 懒标记：该区间待加的公差

    SegmentTreeAP(int n = 0) {
        init(n);
    }

    void init(int size) {
        n = size;
        sum.assign(n * 4 + 5, 0);
        first.assign(n * 4 + 5, 0);
        diff.assign(n * 4 + 5, 0);
    }

    void pull(int p) {
        sum[p] = sum[p << 1] + sum[p << 1 | 1];
    }

    // 节点 p 的整段区间 [l, r] 加上首项 f、公差 d 的等差数列。
    // 区间和增加 len*f + d*len*(len-1)/2（首项到末项求和）。
    void apply(int p, int l, int r, ll f, ll d) {
        ll len = r - l + 1;
        sum[p] += len * f + d * len * (len - 1) / 2;
        first[p] += f;
        diff[p] += d;
    }

    // 把节点 p 的懒标记下传给两个儿子。
    void push(int p, int l, int r) {
        if (first[p] == 0 && diff[p] == 0)
            return;
        int mid = (l + r) >> 1;
        apply(p << 1, l, mid, first[p], diff[p]);
        // 右儿子左端位置是 mid+1，首项要平移 (mid + 1 - l) * diff。
        apply(p << 1 | 1, mid + 1, r, first[p] + (mid + 1 - l) * diff[p], diff[p]);
        first[p] = 0;
        diff[p] = 0;
    }

    void build(int l, int r, int p = 1) {
        if (l == r) {
            sum[p] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(l, mid, p << 1);
        build(mid + 1, r, p << 1 | 1);
        pull(p);
    }

    // 区间 [ql, qr] 加上首项 K、公差 D 的等差数列：
    // 位置 i 增加 K + (i - ql) * D。
    void add_ap(int ql, int qr, ll K, ll D, int l, int r, int p = 1) {
        if (ql <= l && r <= qr) {
            apply(p, l, r, K + (l - ql) * D, D);
            return;
        }
        push(p, l, r);
        int mid = (l + r) >> 1;
        if (ql <= mid)
            add_ap(ql, qr, K, D, l, mid, p << 1);
        if (qr > mid)
            add_ap(ql, qr, K, D, mid + 1, r, p << 1 | 1);
        pull(p);
    }

    // 单点查询位置 pos 的当前值。
    ll query(int pos, int l, int r, int p = 1) {
        if (l == r)
            return sum[p];
        push(p, l, r);
        int mid = (l + r) >> 1;
        if (pos <= mid)
            return query(pos, l, mid, p << 1);
        return query(pos, mid + 1, r, p << 1 | 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    SegmentTreeAP seg(n);
    seg.build(1, n);

    while (m--) {
        int opt;
        cin >> opt;
        if (opt == 1) {
            int l, r;
            ll K, D;
            cin >> l >> r >> K >> D;
            seg.add_ap(l, r, K, D, 1, n);
        } else {
            int p;
            cin >> p;
            cout << seg.query(p, 1, n) << '\n';
        }
    }

    return 0;
}
