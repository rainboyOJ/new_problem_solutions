#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<ll> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    ll ans = 0;
    for (int right = 1; right <= n; ++right) {
        ll sum = 0;
        for (int left = right; left >= 1 && right - left <= k; --left) {
            sum += a[left];
            ans = max(ans, sum);
        }
    }

    cout << ans << '\n';
    return 0;
}
