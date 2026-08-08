#include <bits/stdc++.h>
using namespace std;

const int MAXQ = 100000 + 5;

int q;
long long mod_value;
long long seg[MAXQ << 2];

void build(int u, int l, int r) {
    seg[u] = 1 % mod_value;
    if (l == r) {
        return;
    }

    int mid = (l + r) >> 1;
    build(u << 1, l, mid);
    build(u << 1 | 1, mid + 1, r);
}

void update(int u, int l, int r, int pos, long long val) {
    if (l == r) {
        seg[u] = val % mod_value;
        return;
    }

    int mid = (l + r) >> 1;
    if (pos <= mid) {
        update(u << 1, l, mid, pos, val);
    } else {
        update(u << 1 | 1, mid + 1, r, pos, val);
    }

    seg[u] = seg[u << 1] * seg[u << 1 | 1] % mod_value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> q >> mod_value;
        build(1, 1, q);

        for (int i = 1; i <= q; i++) {
            int op;
            long long x;
            cin >> op >> x;
            if (op == 1) {
                update(1, 1, q, i, x);
            } else {
                // 删除第 x 次乘法操作，相当于把对应位置恢复成乘法单位元 1。
                update(1, 1, q, (int)x, 1);
            }
            cout << seg[1] % mod_value << '\n';
        }
    }

    return 0;
}
