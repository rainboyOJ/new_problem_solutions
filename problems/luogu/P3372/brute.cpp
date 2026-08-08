#include <bits/stdc++.h>
using namespace std;

// brute.cpp：直接修改和求和，复杂度 O(nm)，只适合小数据对拍。

const int MAXN = 505;

int n, m;
long long a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        int op, x, y;
        cin >> op >> x >> y;
        if (op == 1) {
            long long k;
            cin >> k;
            for (int j = x; j <= y; j++) {
                a[j] += k;
            }
        } else {
            long long sum = 0;
            for (int j = x; j <= y; j++) {
                sum += a[j];
            }
            cout << sum << '\n';
        }
    }

    return 0;
}
