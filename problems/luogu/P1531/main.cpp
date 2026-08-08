#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n, m;
int a[MAXN];
int seg[MAXN << 2];

void push_up(int u) {
    seg[u] = max(seg[u << 1], seg[u << 1 | 1]);
}

void build(int u, int l, int r) {
    if (l == r) {
        seg[u] = a[l];
        return;
    }

    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
    push_up(u);
}

void update(int u, int l, int r, int pos, int val) {
    if (l == r) {
        // 题目要求的是把成绩改成 max(原成绩, 新成绩)。
        seg[u] = max(seg[u], val);
        return;
    }

    int mid = (l + r) >> 1;
    if (pos <= mid) {
        update(u << 1, l, mid, pos, val);
    } else {
        update(u << 1 | 1, mid + 1, r, pos, val);
    }
    push_up(u);
}

int query(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return seg[u];
    }

    int mid = (l + r) >> 1;
    int ans = 0;
    if (ql <= mid) {
        ans = max(ans, query(u << 1, l, mid, ql, qr));
    }
    if (qr > mid) {
        ans = max(ans, query(u << 1 | 1, mid + 1, r, ql, qr));
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    build(1, 1, n);

    for (int i = 1; i <= m; i++) {
        char op;
        int x, y;
        cin >> op >> x >> y;
        if (op == 'Q') {
            if (x > y) {
                swap(x, y);
            }
            cout << query(1, 1, n, x, y) << '\n';
        } else {
            update(1, 1, n, x, y);
        }
    }

    return 0;
}
