#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    while (k--) {
        long long n, e, d;
        cin >> n >> e >> d;

        bool ok = false;
        for (long long p = 1; p * p <= n; p++) {
            if (n % p != 0) continue;
            long long q = n / p;
            if (e * d == (p - 1) * (q - 1) + 1) {
                cout << p << ' ' << q << '\n';
                ok = true;
                break;
            }
        }
        if (!ok) {
            cout << "NO\n";
        }
    }

    return 0;
}
