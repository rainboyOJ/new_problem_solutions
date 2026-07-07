#include <bits/stdc++.h>
using namespace std;

long long gcd_ll(long long a, long long b) {
    while (b != 0) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long a[3];
    cin >> a[0] >> a[1] >> a[2];
    sort(a, a + 3);

    long long numerator = a[0];   // 较小锐角的对边是最短边
    long long denominator = a[2]; // 斜边是最长边
    long long g = gcd_ll(numerator, denominator);

    cout << numerator / g << '/' << denominator / g << '\n';
    return 0;
}
