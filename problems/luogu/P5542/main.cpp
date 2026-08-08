#include <bits/stdc++.h>
using namespace std;

const int MAXC = 1000;
int diffv[MAXC + 2][MAXC + 2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        // 题目给出的矩形是 [x1, x2) * [y1, y2)，右上边界本身不被涂色。
        // 因此二维差分的停止位置就是 x2 和 y2。
        diffv[x1][y1]++;
        diffv[x2][y1]--;
        diffv[x1][y2]--;
        diffv[x2][y2]++;
    }

    int ans = 0;
    for (int x = 0; x <= MAXC; x++) {
        for (int y = 0; y <= MAXC; y++) {
            if (x > 0) diffv[x][y] += diffv[x - 1][y];
            if (y > 0) diffv[x][y] += diffv[x][y - 1];
            if (x > 0 && y > 0) diffv[x][y] -= diffv[x - 1][y - 1];

            // 只有左下角为 (0..999, 0..999) 的单位小方格有面积。
            if (x < MAXC && y < MAXC && diffv[x][y] == k) {
                ans++;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
