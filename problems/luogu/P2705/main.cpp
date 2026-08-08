#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long R, B, C, D, E;
    cin >> R >> B >> C >> D >> E;

    long long ans = R * C + B * D;
    long long gain = 2 * E - C - D;
    if (gain > 0) {
        ans += 1LL * min(R, B) * gain;
    }

    cout << ans << '\n';
    return 0;
}
