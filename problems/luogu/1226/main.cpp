#include <bits/stdc++.h>
using namespace std;

long long a, b, p;

long long fast_power(long long base, long long exp, long long mod) {
    long long ans = 1 % mod;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) {
            ans = ans * base % mod;
        }
        base = base * base % mod;
        exp >>= 1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b >> p;
    cout << a << "^" << b << " mod " << p << "=" << fast_power(a, b, p) << '\n';
    return 0;
}
