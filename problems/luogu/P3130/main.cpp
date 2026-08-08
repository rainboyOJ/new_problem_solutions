#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000 + 5;

int n, q;
long long a[MAXN];
long long seg_sum[MAXN << 2];
long long seg_min[MAXN << 2];
long long lazy_add[MAXN << 2];

void push_up(int u) {
    seg_sum[u] = seg_sum[u << 1] + seg_sum[u << 1 | 1];
    seg_min[u] = min(seg_min[u << 1], seg_min[u << 1 | 1]);
}

void apply_add(int u, int l, int r, long long val) {
    seg_sum[u] += (r - l + 1) * val;
    seg_min[u] += val;
    lazy_add[u] += val;
}

void push_down(int u, int l, int r) {
    if (lazy_add[u] == 0 || l == r) {
        return;
    }

    int mid = (l + r) >> 1;
    apply_add(u << 1, l, mid, lazy_add[u]);
    apply_add(u << 1 | 1, mid + 1, r, lazy_add[u]);
    lazy_add[u] = 0;
}

void build(int u, int l, int r) {
    if (l == r) {
        seg_sum[u] = a[l];
        seg_min[u] = a[l];
        return;
    }

    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    push_up(u);
}

void update(int u, int l, int r, int ql, int qr, long long val) {
    if (ql <= l && r <= qr) {
        apply_add(u, l, r, val);
        return;
    }

    push_down(u, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        update(u << 1, l, mid, ql, qr, val);
    }
    if (qr > mid) {
        update(u << 1 | 1, mid + 1, r, ql, qr, val);
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
        ans += query_sum(u << 1, l, mid, ql, qr);
    }
    if (qr > mid) {
        ans += query_sum(u << 1 | 1, mid + 1, r, ql, qr);
    }
    return ans;
}

long long query_min(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return seg_min[u];
    }

    push_down(u, l, r);
    int mid = (l + r) >> 1;
    long long ans = (1LL << 60);
    if (ql <= mid) {
        ans = min(ans, query_min(u << 1, l, mid, ql, qr));
    }
    if (qr > mid) {
        ans = min(ans, query_min(u << 1 | 1, mid + 1, r, ql, qr));
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    build(1, 1, n);

    while (q--) {
        char op;
        cin >> op;
        if (op == 'P') {
            int l, r;
            long long c;
            cin >> l >> r >> c;
            update(1, 1, n, l, r, c);
        } else if (op == 'M') {
            int l, r;
            cin >> l >> r;
            cout << query_min(1, 1, n, l, r) << '\n';
        } else {
            int l, r;
            cin >> l >> r;
            cout << query_sum(1, 1, n, l, r) << '\n';
        }
    }

    return 0;
}
