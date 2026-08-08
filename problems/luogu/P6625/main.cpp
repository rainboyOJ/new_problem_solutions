#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    ll prefix_sum = 0;
    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        ll x;
        cin >> x;
        prefix_sum += x;

        // 每一次操作都对应选择一个更长的前缀，产生一次新的前缀和收益。
        if (i >= 2 && prefix_sum > 0) {
            ans += prefix_sum;
        }
    }

    cout << ans << '\n';
    return 0;
}
