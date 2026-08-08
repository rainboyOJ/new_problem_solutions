#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        long long n, a, d;
        cin >> n >> a >> d;

        long long pw2 = 1;
        while ((d & 1LL) == 0) {
            pw2 <<= 1;
            d >>= 1;
        }

        cout << (n - 1) * (pw2 - 1) << '\n';
    }

    return 0;
}
