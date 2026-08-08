#include <bits/stdc++.h>
using namespace std;

int l, r;

// 统计单个整数中数字 2 出现了多少次。
int count_two(int x) {
    int cnt = 0;
    while (x > 0) {
        if (x % 10 == 2) {
            cnt++;
        }
        x /= 10;
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
