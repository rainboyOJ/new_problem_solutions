// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll a, b, c;

void solve() {
    ll day = 1;
    while (true) {
        if (day % a == 0 && day % b == 0 && day % c == 0) {
            cout << day << '\n';
            return;
        }
        day++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b >> c;
    solve();

    return 0;
}
