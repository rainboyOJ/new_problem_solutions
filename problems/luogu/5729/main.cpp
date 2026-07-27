/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int w, d, h; // 长方体的长、深、高
bool removed[25][25][25]; // 被切掉的小方块
int q, ans;

int main() {
    cin >> w >> d >> h >> q;
    int x1, y1, z1, x2, y2, z2;
    for (int k = 1; k <= q; k++) {
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
        // 标记被切掉的区域
        for (int x = x1; x <= x2; x++)
            for (int y = y1; y <= y2; y++)
                for (int z = z1; z <= z2; z++)
                    removed[x][y][z] = true;
    }
    // 统计剩余小方块
    for (int x = 1; x <= w; x++)
        for (int y = 1; y <= d; y++)
            for (int z = 1; z <= h; z++)
                if (!removed[x][y][z]) ans++;
    cout << ans;
    return 0;
}
