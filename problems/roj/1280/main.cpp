/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:50
 * update_at: 2026-10-05 07:50
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 105;

int r, c;
int h[MAXN][MAXN];      // 每个格子的高度
int f[MAXN][MAXN];      // 从该格子出发的最长滑坡长度
int dr[4] = {-1, 1, 0, 0}; // 上下左右四个方向
int dc[4] = {0, 0, -1, 1};

struct Node {
    int h, x, y;
} nodes[MAXN * MAXN];

// 按高度升序排序，得到拓扑序
bool cmp(Node a, Node b) {
    return a.h < b.h;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> r >> c;
    int cnt = 0;
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            cin >> h[i][j];
            cnt++;
            nodes[cnt].h = h[i][j];
            nodes[cnt].x = i;
            nodes[cnt].y = j;
        }
    }

    sort(nodes + 1, nodes + cnt + 1, cmp);

    int ans = 0;
    for (int k = 1; k <= cnt; k++) {
        int x = nodes[k].x;
        int y = nodes[k].y;
        f[x][y] = 1; // 至少包含自己
        for (int d = 0; d < 4; d++) {
            int nx = x + dr[d];
            int ny = y + dc[d];
            if (nx >= 1 && nx <= r && ny >= 1 && ny <= c && h[nx][ny] < h[x][y]) {
                // 邻居更低，且已经处理过（因为按高度升序）
                if (f[nx][ny] + 1 > f[x][y]) {
                    f[x][y] = f[nx][ny] + 1;
                }
            }
        }
        if (f[x][y] > ans) ans = f[x][y];
    }

    cout << ans << endl;
    return 0;
}
