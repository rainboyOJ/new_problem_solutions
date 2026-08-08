#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, m, b, g;
int vis[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> b >> g;

    for (int i = 1; i <= b; i++) {
        int l, r;
        cin >> l >> r;
        for (int row = l; row <= r; row++) {
            for (int col = 1; col <= m; col++) {
                vis[row][col] = 1;
            }
        }
    }

    for (int i = 1; i <= g; i++) {
        int l, r;
        cin >> l >> r;
        for (int col = l; col <= r; col++) {
            for (int row = 1; row <= n; row++) {
                vis[row][col] = 1;
            }
        }
    }

    int ans = 0;
    for (int row = 1; row <= n; row++) {
        for (int col = 1; col <= m; col++) {
            ans += vis[row][col];
        }
    }

    cout << ans << '\n';

    return 0;
}
