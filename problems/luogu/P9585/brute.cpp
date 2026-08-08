#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    int best = INT_MAX;
    for (int mask = 0; mask < (1 << m); mask++) {
        if (__builtin_popcount((unsigned) mask) != n) continue;
        int anger = 0;
        for (int i = 0; i < m; i++) {
            if (((mask >> i) & 1) == 0) continue;
            int left = (i - 1 + m) % m;
            int right = (i + 1) % m;
            anger += (mask >> left) & 1;
            anger += (mask >> right) & 1;
        }
        best = min(best, anger);
    }

    cout << best << '\n';
    return 0;
}
