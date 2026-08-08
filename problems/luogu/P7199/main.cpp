#include <bits/stdc++.h>
using namespace std;

unsigned long long prefix_sum(unsigned long long x) {
    unsigned long long block = x / 9;
    unsigned long long rem = x % 9;
    return block * 45 + rem * (rem + 1) / 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        unsigned long long l, r;
        cin >> l >> r;
        cout << prefix_sum(r) - prefix_sum(l - 1) << '\n';
    }

    return 0;
}
