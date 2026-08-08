#include <bits/stdc++.h>
using namespace std;

long long n;

void solve() {
    if (n == 0) {
        cout << 0 << '\n';
        return;
    }

    int sign = 1;
    if (n < 0) {
        sign = -1;
        n = -n;
    }

    long long ans = 0;
    while (n > 0) {
        ans = ans * 10 + n % 10;
        n /= 10;
    }

    cout << ans * sign << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    solve();

    return 0;
}
