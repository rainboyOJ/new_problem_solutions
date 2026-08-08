#include <bits/stdc++.h>
using namespace std;

int cost[15];

void solve() {
    int hand = 0;   // 手里可用的钱
    int save = 0;   // 存给妈妈的本金

    for (int month = 1; month <= 12; month++) {
        hand += 300;
        if (hand < cost[month]) {
            cout << -month << '\n';
            return;
        }

        hand -= cost[month];

        int deposit = hand / 100 * 100;
        save += deposit;
        hand -= deposit;
    }

    cout << hand + save * 12 / 10 << '\n';
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
