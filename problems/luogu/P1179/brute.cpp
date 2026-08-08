// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int l, r;

int count_two(int x) {
    string s = to_string(x);
    int cnt = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (s[i] == '2') {
            cnt++;
        }
    }
    return cnt;
}

void solve() {
    int ans = 0;
    for (int i = l; i <= r; i++) {
        ans += count_two(i);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> l >> r;
    solve();

    return 0;
}
