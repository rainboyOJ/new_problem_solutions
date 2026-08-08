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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;

    while (T--) {
        cin >> a0 >> a1 >> b0 >> b1;

        // brute.cpp：小数据暴力。
        // 直接枚举 1..b1 的所有正整数，检查 gcd / lcm 条件。
        long long ans = 0;

        for (long long x = 1; x <= b1; x++) {
            if (gcd_value(x, a0) == a1 && lcm_value(x, b0) == b1) {
                ans++;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
