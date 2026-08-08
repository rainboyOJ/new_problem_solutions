// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int a, b;

void solve() {
    int money = a * 10 + b;
    int ans = 0;
    while ((ans + 1) * 19 <= money) {
        ans++;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;
    solve();

    return 0;
}
