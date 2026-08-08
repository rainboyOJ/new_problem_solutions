#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;

int n, m;
long long bit[MAXN];
long long a[MAXN];

int lowbit(int x) {
    return x & -x;
}

// 在差分数组上做单点加。
void add(int pos, long long val) {
    for (int i = pos; i <= n; i += lowbit(i)) {
        bit[i] += val;
    }
}

// 查询差分数组前缀和，也就是原数组当前位置的值。
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
        cin >> a[i];
    }

    // 先把原数组转成差分数组，再把差分放进树状数组。
    add(1, a[1]);
    for (int i = 2; i <= n; i++) {
        add(i, a[i] - a[i - 1]);
    }

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            long long k;
            cin >> l >> r >> k;
            add(l, k);
            if (r + 1 <= n) {
                add(r + 1, -k);
            }
        } else {
            int x;
            cin >> x;
            cout << sum(x) << '\n';
        }
    }

    return 0;
}
