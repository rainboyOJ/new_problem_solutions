// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3005;

int n, m;
int a[MAXN];

void solve() {
    int ans = 1e9;

    // 枚举每一个长度为 m 的连续区间，直接把区间和算出来。
    for (int l = 1; l + m - 1 <= n; l++) {
        int r = l + m - 1;
        int sum = 0;
        for (int i = l; i <= r; i++) {
            sum += a[i];
        }
        ans = min(ans, sum);
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    solve();

    return 0;
}
