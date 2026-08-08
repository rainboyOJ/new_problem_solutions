#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

i64 n, m, k, p;
i64 x[100005];

i64 ceil_div(i64 a, i64 b) {
    return (a + b - 1) / b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k >> p;

    if (p == 0) {
        cout << "NO\n";
        return 0;
    }

    if (k == 0) {
        if (p != n) {
            cout << "NO\n";
            return 0;
        }

        cout << "YES\n";
        for (int i = 1; i <= n; i++) {
            cout << 0 << ' ' << m << '\n';
        }
        return 0;
    }

    if (p == n) {
        if (k % n != 0) {
            cout << "NO\n";
            return 0;
        }

        i64 same = k / n;
        if (same > m) {
            cout << "NO\n";
            return 0;
        }

        cout << "YES\n";
        for (int i = 1; i <= n; i++) {
            cout << same << ' ' << (m - same) << '\n';
        }
        return 0;
    }

    // 设恰好 p 个人都抽到最大值 t。
    // 那么：
    // 1) 至少要有 p * t 张记号；
    // 2) 其余 n - p 个人每人至多 t - 1 张记号。
    i64 left = max<i64>(1, ceil_div(k + n - p, n));
    i64 right = min<i64>(m, k / p);

    if (left > right) {
        cout << "NO\n";
        return 0;
    }

    i64 t = left;
    i64 rest = k - p * t;

    for (int i = 1; i <= n; i++) {
        x[i] = 0;
    }
    for (int i = 1; i <= p; i++) {
        x[i] = t;
    }

    for (int i = p + 1; i <= n; i++) {
        i64 give = min(rest, t - 1);
        x[i] = give;
        rest -= give;
    }

    cout << "YES\n";
    for (int i = 1; i <= n; i++) {
        cout << x[i] << ' ' << (m - x[i]) << '\n';
    }

    return 0;
}
