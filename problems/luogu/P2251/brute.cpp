#include <bits/stdc++.h>
using namespace std;

int n, m;
int a[1005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // brute.cpp：直接枚举每个长度为 m 的窗口，再在窗口里扫描最小值。
    for (int l = 1; l + m - 1 <= n; l++) {
        int r = l + m - 1;
        int mn = a[l];
        for (int i = l + 1; i <= r; i++) {
            mn = min(mn, a[i]);
        }
        cout << mn << '\n';
    }

    return 0;
}
