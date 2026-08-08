#include <bits/stdc++.h>
using namespace std;

int h[15];
int tao;

void solve() {
    int reach = tao + 30;
    int ans = 0;

    for (int i = 1; i <= 10; i++) {
        if (h[i] <= reach) {
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
