#include <bits/stdc++.h>
using namespace std;

int a, b;

void solve() {
    int ans = 0;
    int mx = 8; // 只有严格大于 8 才会不高兴

    for (int day = 1; day <= 7; day++) {
        cin >> a >> b;
        int sum = a + b;
        if (sum > mx) {
            mx = sum;
            ans = day;
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
