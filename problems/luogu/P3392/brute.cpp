#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;

int n, m;
string s[MAXN];

int row_cost(int row, char target) {
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        if (s[row][i] != target) {
            cnt++;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    int ans = 0x3f3f3f3f;

    // 暴力枚举三段分别有多少行，然后逐行统计改色代价。
    for (int white_rows = 1; white_rows <= n - 2; white_rows++) {
        for (int blue_rows = 1; white_rows + blue_rows <= n - 1; blue_rows++) {
            int red_rows = n - white_rows - blue_rows;
            if (red_rows < 1) {
                continue;
            }

            int cur = 0;
            for (int i = 1; i <= white_rows; i++) {
                cur += row_cost(i, 'W');
            }
            for (int i = white_rows + 1; i <= white_rows + blue_rows; i++) {
                cur += row_cost(i, 'B');
            }
            for (int i = white_rows + blue_rows + 1; i <= n; i++) {
                cur += row_cost(i, 'R');
            }

            ans = min(ans, cur);
        }
    }

    cout << ans << '\n';

    return 0;
}
