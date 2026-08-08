// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int a, b;

void solve() {
    int ans = 0;
    int unhappy = 0; // 记录当前最大的不高兴程度

    for (int day = 1; day <= 7; day++) {
        cin >> a >> b;
        int sum = a + b;
        if (sum > 8) {
            int cur = sum - 8;
            if (cur > unhappy) {
                unhappy = cur;
                ans = day;
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
