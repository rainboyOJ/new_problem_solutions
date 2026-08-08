#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;

    long long ans = 0;
    for (int day_value = 1; k > 0; day_value++) {
        int use_days = min(k, day_value);
        ans += 1LL * use_days * day_value;
        k -= use_days;
    }

    cout << ans << '\n';
    return 0;
}
