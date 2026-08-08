#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接维护原数组。
// 区间加时逐个位置修改，单点查询时直接输出。

const int MAXN = 500005;

int n, m;
long long a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    while (m--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            long long k;
            cin >> l >> r >> k;
            for (int i = l; i <= r; i++) {
                a[i] += k;
            }
        } else {
            int x;
            cin >> x;
            cout << a[x] << '\n';
        }
    }

    return 0;
}
