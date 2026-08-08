// brute.cpp：小数据暴力解，直接连乘 b 次计算 a^b mod p。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a, b, p;
    cin >> a >> b >> p;

    long long ans = 1 % p;
    for (long long i = 1; i <= b; i++) {
        ans = ans * (a % p) % p;
    }

    cout << a << "^" << b << " mod " << p << "=" << ans << '\n';
    return 0;
}
