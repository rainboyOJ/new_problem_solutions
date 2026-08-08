#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3005;

int n, m;
int a[MAXN];

void solve() {
    int sum = 0;
    for (int i = 1; i <= m; i++) {
        sum += a[i];
    }

    int ans = sum;
    for (int i = m + 1; i <= n; i++) {
        sum += a[i];
        sum -= a[i - m];
        ans = min(ans, sum);
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
