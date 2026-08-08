#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k;
    cin >> n >> k;

    long long ans = n;
    while (n >= k) {
        long long extra = n / k;
        ans += extra;
        n = extra + n % k;
    }

    cout << ans << '\n';
    return 0;
}
