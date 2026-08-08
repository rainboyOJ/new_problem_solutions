/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int a[15][15]; // 蛇形方阵
int n;

// 方向: 右、下、左、上
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int main() {
    cin >> n;
    int x = 1, y = 1, dir = 0;
    for (int v = 1; v <= n * n; v++) {
        a[x][y] = v;
        // 尝试沿当前方向走下一步
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        // 如果越界或已填数，右转方向
        if (nx < 1 || nx > n || ny < 1 || ny > n || a[nx][ny] != 0) {
            dir = (dir + 1) % 4;
            nx = x + dx[dir];
            ny = y + dy[dir];
        }
        x = nx;
        y = ny;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            printf("%3d", a[i][j]);
        printf("\n");
    }
    return 0;
}
