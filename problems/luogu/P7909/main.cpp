#include <bits/stdc++.h>
using namespace std;

long long solve(long long n, long long l, long long r) {
    if (l / n == r / n) return r % n;
    return n - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, l, r;
    cin >> n >> l >> r;
    cout << solve(n, l, r) << '\n';
    return 0;
}
