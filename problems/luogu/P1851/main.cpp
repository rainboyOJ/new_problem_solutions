#include <bits/stdc++.h>
using namespace std;

int sum_proper_divisors(int x) {
    if (x == 1) return 0;
    int sum = 1;
    for (int d = 2; 1LL * d * d <= x; d++) {
        if (x % d) continue;
        sum += d;
        if (d * d != x) sum += x / d;
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int s;
    cin >> s;

    for (int a = s;; a++) {
        int b = sum_proper_divisors(a);
        if (b <= a) continue;
        if (sum_proper_divisors(b) == a) {
            cout << a << ' ' << b << '\n';
            return 0;
        }
    }

    return 0;
}
