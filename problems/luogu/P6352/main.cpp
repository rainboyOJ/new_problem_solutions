#include <bits/stdc++.h>
using namespace std;

int a[3];

void solve() {
    sort(a, a + 3);

    int d1 = a[1] - a[0];
    int d2 = a[2] - a[1];

    // 三个数本身已成等差时，按样例风格补在右侧。
    if (d1 == d2) {
        cout << a[2] + d1 << '\n';
        return;
    }

    if (d1 < d2) {
        cout << a[1] + d1 << '\n';
    } else {
        cout << a[0] + d2 << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a[0] >> a[1] >> a[2];
    solve();

    return 0;
}
