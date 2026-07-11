/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:35
 * update_at: 2026-07-11 13:39
 */
// brute.cpp：小数据校验解，用坐标和有向面积判断方向。
#include <bits/stdc++.h>
using namespace std;

void move_one(char ch, int &x, int &y) {
    if (ch == 'N') y++;
    if (ch == 'S') y--;
    if (ch == 'E') x++;
    if (ch == 'W') x--;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int tc = 1; tc <= n; tc++) {
        string s;
        cin >> s;

        int x = 0;
        int y = 0;
        long long area2 = 0; // 多边形有向面积的 2 倍。

        for (int i = 0; i < (int)s.size(); i++) {
            int nx = x;
            int ny = y;
            move_one(s[i], nx, ny);

            area2 += 1ll * x * ny - 1ll * nx * y;

            x = nx;
            y = ny;
        }

        if (area2 > 0) {
            cout << "CCW\n";
        } else {
            cout << "CW\n";
        }
    }

    return 0;
}
