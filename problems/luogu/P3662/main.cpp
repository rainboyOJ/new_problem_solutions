#include <bits/stdc++.h>
using namespace std;

const int maxn = 100000 + 5;

int n, k, b;
int bad[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> b;

    for (int i = 1; i <= b; i++) {
        int x;
        cin >> x;
        bad[x] = 1;
    }

    int cur = 0;
    for (int i = 1; i <= k; i++) {
        cur += bad[i];
    }

    int ans = cur;
    for (int r = k + 1; r <= n; r++) {
        cur += bad[r];
        cur -= bad[r - k];
        ans = min(ans, cur);
    }

    cout << ans << '\n';
    return 0;
}
