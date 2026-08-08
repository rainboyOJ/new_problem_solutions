#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接维护数组。
// 查询时暴力扫区间，修改时做 max 更新。

const int MAXN = 200005;

int n, m;
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= m; i++) {
        char op;
        int x, y;
        cin >> op >> x >> y;
        if (op == 'Q') {
            if (x > y) {
                swap(x, y);
            }
            int ans = 0;
            for (int j = x; j <= y; j++) {
                ans = max(ans, a[j]);
            }
            cout << ans << '\n';
        } else {
            a[x] = max(a[x], y);
        }
    }

    return 0;
}
