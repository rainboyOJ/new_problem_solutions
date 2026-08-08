#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, m;
long long a[MAXN];
long long tree_sum[MAXN * 4]; // tree_sum[p] 表示当前线段树节点覆盖区间的和。
long long lazy_add[MAXN * 4]; // lazy_add[p] 表示还没有下传给孩子的区间加标记。

void build(int p, int l, int r) {
    if (l == r) {
        tree_sum[p] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(p * 2, l, mid);
    build(p * 2 + 1, mid + 1, r);
    tree_sum[p] = tree_sum[p * 2] + tree_sum[p * 2 + 1];
}

void apply_add(int p, int l, int r, long long value) {
    tree_sum[p] += value * (r - l + 1);
    lazy_add[p] += value;
}

void push_down(int p, int l, int r) {
    if (lazy_add[p] == 0 || l == r) {
        return;
    }
    int mid = (l + r) / 2;
    apply_add(p * 2, l, mid, lazy_add[p]);
    apply_add(p * 2 + 1, mid + 1, r, lazy_add[p]);
    lazy_add[p] = 0;
}

void range_add(int p, int l, int r, int ql, int qr, long long value) {
    if (ql <= l && r <= qr) {
        apply_add(p, l, r, value);
        return;
    }
    push_down(p, l, r);
    int mid = (l + r) / 2;
    if (ql <= mid) {
        range_add(p * 2, l, mid, ql, qr, value);
    }
    if (qr > mid) {
        range_add(p * 2 + 1, mid + 1, r, ql, qr, value);
    }
    tree_sum[p] = tree_sum[p * 2] + tree_sum[p * 2 + 1];
}

long long query_sum(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return tree_sum[p];
    }
    push_down(p, l, r);
    int mid = (l + r) / 2;
    long long answer = 0;
    if (ql <= mid) {
        answer += query_sum(p * 2, l, mid, ql, qr);
    }
    if (qr > mid) {
        answer += query_sum(p * 2 + 1, mid + 1, r, ql, qr);
    }
    return answer;
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
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            long long k;
            cin >> k;
            range_add(1, 1, n, x, y, k);
        } else {
            cout << query_sum(1, 1, n, x, y) << '\n';
        }
    }

    return 0;
}
