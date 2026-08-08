#include <bits/stdc++.h>
using namespace std;

int sum_proper_divisors(int x) {
    int sum = 0;
    for (int d = 1; d < x; d++) {
        if (x % d == 0) sum += d;
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
