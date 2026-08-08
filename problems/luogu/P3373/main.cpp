#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

int n, q;
long long mod_value;
long long a[MAXN];
long long seg_sum[MAXN << 2];
long long lazy_mul[MAXN << 2];
long long lazy_add[MAXN << 2];

void push_up(int u) {
    seg_sum[u] = (seg_sum[u << 1] + seg_sum[u << 1 | 1]) % mod_value;
}

void apply_mul(int u, int l, int r, long long val) {
    seg_sum[u] = seg_sum[u] * val % mod_value;
    lazy_mul[u] = lazy_mul[u] * val % mod_value;
    lazy_add[u] = lazy_add[u] * val % mod_value;
}

void apply_add(int u, int l, int r, long long val) {
    seg_sum[u] = (seg_sum[u] + (r - l + 1) * val) % mod_value;
    lazy_add[u] = (lazy_add[u] + val) % mod_value;
}

void push_down(int u, int l, int r) {
    if (l == r) {
        lazy_mul[u] = 1;
        lazy_add[u] = 0;
        return;
    }

    int mid = (l + r) >> 1;
    if (lazy_mul[u] != 1) {
        apply_mul(u << 1, l, mid, lazy_mul[u]);
        apply_mul(u << 1 | 1, mid + 1, r, lazy_mul[u]);
        lazy_mul[u] = 1;
    }
    if (lazy_add[u] != 0) {
        apply_add(u << 1, l, mid, lazy_add[u]);
        apply_add(u << 1 | 1, mid + 1, r, lazy_add[u]);
        lazy_add[u] = 0;
    }
}

void build(int u, int l, int r) {
    lazy_mul[u] = 1;
    lazy_add[u] = 0;

    if (l == r) {
        seg_sum[u] = a[l] % mod_value;
        return;
    }

    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    push_up(u);
}

void range_mul(int u, int l, int r, int ql, int qr, long long val) {
    if (ql <= l && r <= qr) {
        apply_mul(u, l, r, val);
        return;
    }

    push_down(u, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        range_mul(u << 1, l, mid, ql, qr, val);
    }
    if (qr > mid) {
        range_mul(u << 1 | 1, mid + 1, r, ql, qr, val);
    }
    push_up(u);
}

void range_add(int u, int l, int r, int ql, int qr, long long val) {
    if (ql <= l && r <= qr) {
        apply_add(u, l, r, val);
        return;
    }

    push_down(u, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        range_add(u << 1, l, mid, ql, qr, val);
    }
    if (qr > mid) {
        range_add(u << 1 | 1, mid + 1, r, ql, qr, val);
    }
    push_up(u);
}

long long query_sum(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return seg_sum[u];
    }

    push_down(u, l, r);
    int mid = (l + r) >> 1;
    long long ans = 0;
    if (ql <= mid) {
        ans = (ans + query_sum(u << 1, l, mid, ql, qr)) % mod_value;
    }
    if (qr > mid) {
        ans = (ans + query_sum(u << 1 | 1, mid + 1, r, ql, qr)) % mod_value;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q >> mod_value;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    build(1, 1, n);

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            range_mul(1, 1, n, l, r, x % mod_value);
        } else if (op == 2) {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            range_add(1, 1, n, l, r, x % mod_value);
        } else {
            int l, r;
            cin >> l >> r;
            cout << query_sum(1, 1, n, l, r) % mod_value << '\n';
        }
    }

    return 0;
}
