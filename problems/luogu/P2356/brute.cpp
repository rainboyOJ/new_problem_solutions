// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
int a[MAXN][MAXN];

void solve() {
    int ans = 0;

    // 枚举每一个空位，真的把该行该列的敌人全部统计一遍。
    for (int x = 1; x <= n; x++) {
        for (int y = 1; y <= n; y++) {
            if (a[x][y] != 0) {
                continue;
            }

            int cur = 0;
            for (int j = 1; j <= n; j++) {
                cur += a[x][j];
            }
            for (int i = 1; i <= n; i++) {
                cur += a[i][y];
            }

            ans = max(ans, cur);
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
        }
    }

    solve();

    return 0;
}
