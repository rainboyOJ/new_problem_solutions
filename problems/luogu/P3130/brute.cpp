#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接维护原数组。
// 区间加时逐个修改，查询最小值和区间和时逐个扫描。

const int MAXN = 200000 + 5;

int n, q;
long long a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    while (q--) {
        char op;
        cin >> op;
        if (op == 'P') {
            int l, r;
            long long c;
            cin >> l >> r >> c;
            for (int i = l; i <= r; i++) {
                a[i] += c;
            }
        } else if (op == 'M') {
            int l, r;
            cin >> l >> r;
            long long ans = (1LL << 60);
            for (int i = l; i <= r; i++) {
                ans = min(ans, a[i]);
            }
            cout << ans << '\n';
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
