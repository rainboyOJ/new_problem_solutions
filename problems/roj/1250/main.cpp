/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:02
 * update_at: 2026-10-05 07:03
 */
#include <cstdio>

typedef long long ll;

const int MAXN = 55;

int m, n;                       // m 行（南北方向），n 列（东西方向）
int wall[MAXN][MAXN];           // wall[r][c]：该方块的墙位和，1西 2北 4东 8南
bool vis[MAXN][MAXN];           // 洪水填充的访问标记

// 四个方向：行增量、列增量、当前格这一侧对应的墙位
const int DR[4] = {-1, 1, 0, 0};
const int DC[4] = {0, 0, -1, 1};
const int BIT[4] = {2, 8, 1, 4};

// 从 (sr, sc) 出发洪水填充，返回这个房间（连通分量）的面积
// 室内的墙被相邻两格各定义一次，只查当前格自己那一侧的墙位即可
int dfs(int sr, int sc) {
    if (sr < 0 || sr >= m || sc < 0 || sc >= n) return 0; // 越界保护
    if (vis[sr][sc]) return 0;
    vis[sr][sc] = true;
    int size = 1;
    for (int d = 0; d < 4; ++d) {
        if (wall[sr][sc] & BIT[d]) continue; // 这一侧有墙，过不去
        size += dfs(sr + DR[d], sc + DC[d]);
    }
    return size;
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            scanf("%d", &wall[i][j]);

    int room_count = 0; // 房间总数
    int best = 0;       // 最大房间面积
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (!vis[i][j]) {
                ++room_count;
                int size = dfs(i, j);
                if (size > best) best = size;
            }

    printf("%d\n%d\n", room_count, best);
    return 0;
}
