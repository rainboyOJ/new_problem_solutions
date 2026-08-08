#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, m;
int diff_map[MAXN + 2][MAXN + 2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= m; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        // 二维差分：让矩形 [x1..x2][y1..y2] 整体加 1。
        diff_map[x1][y1] += 1;
        diff_map[x2 + 1][y1] -= 1;
        diff_map[x1][y2 + 1] -= 1;
        diff_map[x2 + 1][y2 + 1] += 1;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            diff_map[i][j] += diff_map[i - 1][j] + diff_map[i][j - 1] - diff_map[i - 1][j - 1];
            if (j > 1) cout << ' ';
            cout << diff_map[i][j];
        }
        cout << '\n';
    }

    return 0;
}
