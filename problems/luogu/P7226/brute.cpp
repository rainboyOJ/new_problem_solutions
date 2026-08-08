#include <bits/stdc++.h>
using namespace std;

long long qpow(long long a, int b) {
    long long res = 1;
    while (b--) res *= a;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        long long x;
        cin >> x;
        int p = x % 10;
        long long num = x / 10;
        ans += qpow(num, p);
    }

    cout << ans << '\n';
    return 0;
}
