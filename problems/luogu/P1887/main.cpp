#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, m;
    cin >> n >> m;

    long long base = n / m;
    long long extra = n % m;

    bool first = true;
    for (long long i = 0; i < m - extra; i++) {
        if (!first) cout << ' ';
        cout << base;
        first = false;
    }
    for (long long i = 0; i < extra; i++) {
        if (!first) cout << ' ';
        cout << base + 1;
        first = false;
    }
    cout << '\n';

    return 0;
}
