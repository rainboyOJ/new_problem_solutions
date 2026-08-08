#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m;
int a[MAXN];

void solve() {
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            for (int k = j + 1; k <= n; k++) {
                int sum = a[i] + a[j] + a[k];
                if (sum <= m) {
                    ans = max(ans, sum);
                }
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    solve();

    return 0;
}
