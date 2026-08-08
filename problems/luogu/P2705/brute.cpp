#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long R, B, C, D, E;
    cin >> R >> B >> C >> D >> E;

    long long ans = LLONG_MIN;
    for (long long t = 0; t <= min(R, B); t++) {
        long long cur = (R - t) * C + (B - t) * D + 2 * t * E;
        ans = max(ans, cur);
    }

    cout << ans << '\n';
    return 0;
}
