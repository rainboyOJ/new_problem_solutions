/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int NEG = -1000000000;

int n;
int grid[22][22];
// cur[r1][r2]：两人同在斜线 k = 行+列 上、分别位于 (r1, k-r1)、(r2, k-r2) 时的最大和
int cur[22][22], nxt[22][22];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    while (true) {
        int r, c, v;
        cin >> r >> c >> v;
        if (r == 0 && c == 0 && v == 0) break;
        grid[r][c] = v;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            cur[i][j] = NEG;
    cur[1][1] = grid[1][1];

    for (int k = 3; k <= 2 * n; k++) {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                nxt[i][j] = NEG;
        int lo = max(1, k - n), hi = min(n, k - 1);
        for (int r1 = lo; r1 <= hi; r1++) {
            int g1 = grid[r1][k - r1];
            for (int r2 = lo; r2 <= hi; r2++) {
                int gain = (r1 == r2) ? g1 : g1 + grid[r2][k - r2];
                int best = NEG;
                for (int p1 = r1 - 1; p1 <= r1; p1++)
                    for (int p2 = r2 - 1; p2 <= r2; p2++)
                        if (p1 >= 1 && p2 >= 1 && cur[p1][p2] > best)
                            best = cur[p1][p2];
                if (best > NEG) nxt[r1][r2] = best + gain;
            }
        }
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cur[i][j] = nxt[i][j];
    }
    cout << cur[n][n] << "\n";
    return 0;
}
