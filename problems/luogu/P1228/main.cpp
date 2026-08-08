/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

int k, sz, cnt;
int ans[10000][3];

void cover(int top, int left, int size, int sx, int sy) {
    if (size == 1) return;
    int half = size / 2;
    int mx = top + half - 1, my = left + half - 1;
    if (sx <= mx && sy <= my) {
        ans[cnt][0] = mx + 1; ans[cnt][1] = my + 1; ans[cnt][2] = 1; cnt++;
        cover(top, left, half, sx, sy);
        cover(top, left + half, half, mx, my + 1);
        cover(top + half, left, half, mx + 1, my);
        cover(top + half, left + half, half, mx + 1, my + 1);
    } else if (sx <= mx && sy > my) {
        ans[cnt][0] = mx + 1; ans[cnt][1] = my; ans[cnt][2] = 2; cnt++;
        cover(top, left, half, mx, my);
        cover(top, left + half, half, sx, sy);
        cover(top + half, left, half, mx + 1, my);
        cover(top + half, left + half, half, mx + 1, my + 1);
    } else if (sx > mx && sy <= my) {
        ans[cnt][0] = mx; ans[cnt][1] = my + 1; ans[cnt][2] = 3; cnt++;
        cover(top, left, half, mx, my);
        cover(top, left + half, half, mx, my + 1);
        cover(top + half, left, half, sx, sy);
        cover(top + half, left + half, half, mx + 1, my + 1);
    } else {
        ans[cnt][0] = mx; ans[cnt][1] = my; ans[cnt][2] = 4; cnt++;
        cover(top, left, half, mx, my);
        cover(top, left + half, half, mx, my + 1);
        cover(top + half, left, half, mx + 1, my);
        cover(top + half, left + half, half, sx, sy);
    }
}

int main() {
    int x, y;
    cin >> k >> x >> y;
    sz = 1 << k;
    cover(1, 1, sz, x, y);
    for (int i = 0; i < cnt; i++)
        cout << ans[i][0] << " " << ans[i][1] << " " << ans[i][2] << endl;
    return 0;
}
