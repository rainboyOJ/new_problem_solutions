#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
int a[MAXN][MAXN];
int row_sum[MAXN];
int col_sum[MAXN];

void solve() {
    int ans = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i][j] == 0) {
                ans = max(ans, row_sum[i] + col_sum[j]);
            }
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            row_sum[i] += a[i][j];
            col_sum[j] += a[i][j];
        }
    }

    solve();

    return 0;
}
