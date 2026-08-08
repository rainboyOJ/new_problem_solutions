/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

int r, c, k;
char grid[105][105];

int main() {
    cin >> r >> c >> k;
    for (int i = 0; i < r; i++) cin >> grid[i];
    if (k == 1) {
        int ans = 0;
        for (int i = 0; i < r; i++)
            for (int j = 0; j < c; j++)
                if (grid[i][j] == '.') ans++;
        cout << ans << endl;
        return 0;
    }
    int ans = 0;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j <= c - k; j++) {
            bool ok = true;
            for (int t = 0; t < k; t++)
                if (grid[i][j + t] != '.') { ok = false; break; }
            if (ok) ans++;
        }
    }
    for (int i = 0; i <= r - k; i++) {
        for (int j = 0; j < c; j++) {
            bool ok = true;
            for (int t = 0; t < k; t++)
                if (grid[i + t][j] != '.') { ok = false; break; }
            if (ok) ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
