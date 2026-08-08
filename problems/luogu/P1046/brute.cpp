// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int h[15];
int tao;

void solve() {
    int ans = 0;

    // 逐个判断每个苹果能不能碰到。
    for (int i = 1; i <= 10; i++) {
        if (h[i] <= tao + 30) {
            ans++;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 1; i <= 10; i++) {
        cin >> h[i];
    }
    cin >> tao;

    solve();

    return 0;
}
