#include <bits/stdc++.h>
using namespace std;

unsigned long long digit_root(unsigned long long x) {
    while (x >= 10) {
        unsigned long long sum = 0;
        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }
        x = sum;
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        unsigned long long l, r;
        cin >> l >> r;
        unsigned long long ans = 0;
        for (unsigned long long x = l; x <= r; x++) {
            ans += digit_root(x);
        }
        cout << ans << '\n';
    }

    return 0;
}
