#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;

int n, m;
long long bit[MAXN];

int lowbit(int x) {
    return x & -x;
}

// 单点增加：让 a[pos] += val
void add(int pos, long long val) {
    for (int i = pos; i <= n; i += lowbit(i)) {
        bit[i] += val;
    }
}

// 查询前缀和 a[1] + ... + a[pos]
long long sum(int pos) {
    long long ret = 0;
    for (int i = pos; i > 0; i -= lowbit(i)) {
        ret += bit[i];
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        long long x;
        cin >> x;
        add(i, x);
    }

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x;
            long long k;
            cin >> x >> k;
            add(x, k);
        } else {
            int l, r;
            cin >> l >> r;
            cout << sum(r) - sum(l - 1) << '\n';
        }
    }

    return 0;
}
