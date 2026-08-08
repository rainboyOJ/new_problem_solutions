#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接维护原数组。
// 区间乘、区间加都逐个修改，查询时逐个累加并取模。

const int MAXN = 100000 + 5;

int n, q;
long long mod_value;
long long a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q >> mod_value;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] %= mod_value;
    }

    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            x %= mod_value;
            for (int i = l; i <= r; i++) {
                a[i] = a[i] * x % mod_value;
            }
        } else if (op == 2) {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            x %= mod_value;
            for (int i = l; i <= r; i++) {
                a[i] = (a[i] + x) % mod_value;
            }
        } else {
            int l, r;
            cin >> l >> r;
            long long ans = 0;
            for (int i = l; i <= r; i++) {
                ans = (ans + a[i]) % mod_value;
            }
            cout << ans % mod_value << '\n';
        }
    }

    return 0;
}
