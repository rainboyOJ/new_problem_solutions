#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

int n, m;
int seg[MAXN << 2];
int lazy_rev[MAXN << 2];

void push_up(int u) {
    seg[u] = seg[u << 1] + seg[u << 1 | 1];
}

void apply_reverse(int u, int l, int r) {
    seg[u] = (r - l + 1) - seg[u];
    lazy_rev[u] ^= 1;
}

void push_down(int u, int l, int r) {
    if (lazy_rev[u] == 0 || l == r) {
        return;
    }

    int mid = (l + r) >> 1;
    apply_reverse(u << 1, l, mid);
    apply_reverse(u << 1 | 1, mid + 1, r);
    lazy_rev[u] = 0;
}

void update(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        apply_reverse(u, l, r);
        return;
    }

    push_down(u, l, r);
    int mid = (l + r) >> 1;
    if (ql <= mid) {
        update(u << 1, l, mid, ql, qr);
    }
    if (qr > mid) {
        update(u << 1 | 1, mid + 1, r, ql, qr);
    }
    push_up(u);
}

int query(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return seg[u];
    }

    push_down(u, l, r);
    int mid = (l + r) >> 1;
    int ans = 0;
    if (ql <= mid) {
        ans += query(u << 1, l, mid, ql, qr);
    }
    if (qr > mid) {
        ans += query(u << 1 | 1, mid + 1, r, ql, qr);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 0) {
            update(1, 1, n, l, r);
        } else {
            cout << query(1, 1, n, l, r) << '\n';
        }
    }

    return 0;
}
