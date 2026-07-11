/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:31
 * update_at: 2026-07-11 15:34
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n, q;
int left_xy[MAXN][MAXN]; // 固定 x,y，沿 z 方向还剩多少块。
int left_xz[MAXN][MAXN]; // 固定 x,z，沿 y 方向还剩多少块。
int left_yz[MAXN][MAXN]; // 固定 y,z，沿 x 方向还剩多少块。
long long ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            left_xy[i][j] = n;
            left_xz[i][j] = n;
            left_yz[i][j] = n;
        }
    }

    while (q--) {
        int x, y, z;
        cin >> x >> y >> z;

        left_xy[x][y]--;
        if (left_xy[x][y] == 0) ans++;

        left_xz[x][z]--;
        if (left_xz[x][z] == 0) ans++;

        left_yz[y][z]--;
        if (left_yz[y][z] == 0) ans++;

        cout << ans << '\n';
    }

    return 0;
}
