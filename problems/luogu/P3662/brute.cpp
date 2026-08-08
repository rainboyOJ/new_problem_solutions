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

    int ans = k;
    for (int l = 1; l + k - 1 <= n; l++) {
        int cnt = 0;
        for (int i = l; i < l + k; i++) {
            cnt += bad[i];
        }
        ans = min(ans, cnt);
    }

    cout << ans << '\n';
    return 0;
}
