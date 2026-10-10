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

int m, n;
int grid[55][55];
int layer[55][55], nlayer[55][55];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> m >> n;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> grid[i][j];

    for (int i = 0; i <= m; i++)
        for (int j = 0; j <= m; j++)
            layer[i][j] = NEG;
    layer[1][1] = grid[0][0];

    for (int k = 3; k <= m + n; k++) {
        for (int i = 0; i <= m; i++)
            for (int j = 0; j <= m; j++)
                nlayer[i][j] = NEG;
        int lo = max(1, k - n), hi = min(m, k - 1);
        for (int x1 = lo; x1 <= hi; x1++) {
            int v1 = grid[x1 - 1][k - x1 - 1];
            for (int x2 = lo; x2 <= hi; x2++) {
                int best = NEG;
                for (int p1 = x1; p1 >= x1 - 1 && p1 >= 1; p1--)
                    for (int p2 = x2; p2 >= x2 - 1 && p2 >= 1; p2--)
                        if (layer[p1][p2] > best) best = layer[p1][p2];
                if (best == NEG) continue;
                int gain = v1 + (x1 != x2 ? grid[x2 - 1][k - x2 - 1] : 0);
                nlayer[x1][x2] = best + gain;
            }
        }
        for (int i = 0; i <= m; i++)
            for (int j = 0; j <= m; j++)
                layer[i][j] = nlayer[i][j];
    }
    cout << layer[m][m] << "\n";
    return 0;
}
