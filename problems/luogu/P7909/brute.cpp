#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, l, r;
    cin >> n >> l >> r;

    long long ans = 0;
    for (long long k = l; k <= r; k++) {
        ans = max(ans, k % n);
    }

    cout << ans << '\n';
    return 0;
}
