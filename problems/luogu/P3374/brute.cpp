#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接用数组维护原数列。
// 单点加时直接修改，区间和查询时暴力累加。

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
            int x;
            long long k;
            cin >> x >> k;
            a[x] += k;
        } else {
            int l, r;
            cin >> l >> r;
            long long ans = 0;
            for (int i = l; i <= r; i++) {
                ans += a[i];
            }
            cout << ans << '\n';
        }
    }

    return 0;
}
