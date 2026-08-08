// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int cost[15];

void solve() {
    int hand = 0;
    int save = 0;

    for (int month = 1; month <= 12; month++) {
        hand += 300;

        if (hand < cost[month]) {
            cout << -month << '\n';
            return;
        }

        hand -= cost[month];

        // 用最直观的方式一百一百地往妈妈那里存。
        while (hand >= 100) {
            hand -= 100;
            save += 100;
        }
    }

    cout << hand + save + save / 5 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 1; i <= 12; i++) {
        cin >> cost[i];
    }

    solve();

    return 0;
}
