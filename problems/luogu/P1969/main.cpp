#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

int n;
long long h[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    long long ans = 0;
    long long prev = 0; // h[0] 视为 0，统一处理第一列

    for (int i = 1; i <= n; i++) {
        if (h[i] > prev) {
            ans += h[i] - prev;
        }
        prev = h[i];
    }

    cout << ans << '\n';
    return 0;
}
