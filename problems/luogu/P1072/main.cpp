#include <bits/stdc++.h>
using namespace std;

int T;
long long a0, a1, b0, b1;

long long gcd_value(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

long long lcm_value(long long a, long long b) {
    return a / gcd_value(a, b) * b;
}

bool check(long long x) {
    return gcd_value(x, a0) == a1 && lcm_value(x, b0) == b1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;

    while (T--) {
        cin >> a0 >> a1 >> b0 >> b1;

        long long ans = 0;

        // 由 lcm(x, b0) = b1 可知 x 一定是 b1 的约数。
        for (long long d = 1; d * d <= b1; d++) {
            if (b1 % d != 0) {
                continue;
            }

            if (check(d)) {
                ans++;
            }

            long long other = b1 / d;
            if (other != d && check(other)) {
                ans++;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
