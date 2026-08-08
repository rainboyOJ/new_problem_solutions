#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> covered(n + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        // 朴素做法：把地毯覆盖的每一个格子都加 1。
        for (int x = x1; x <= x2; ++x) {
            for (int y = y1; y <= y2; ++y) {
                ++covered[x][y];
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (j > 1) cout << ' ';
            cout << covered[i][j];
        }
        cout << '\n';
    }

    return 0;
}
