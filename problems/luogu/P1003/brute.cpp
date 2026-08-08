// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int n;
int a[MAXN], b[MAXN], g[MAXN], k[MAXN];
int x, y;

void solve() {
    int ans = -1;

    // 按铺设顺序检查，后面覆盖到前面时直接更新答案。
    for (int i = 1; i <= n; i++) {
        if (a[i] <= x && x <= a[i] + g[i] &&
            b[i] <= y && y <= b[i] + k[i]) {
            ans = i;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> b[i] >> g[i] >> k[i];
    }
    cin >> x >> y;

    solve();

    return 0;
}
