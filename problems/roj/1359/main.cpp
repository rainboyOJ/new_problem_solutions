/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:00
 * update_at: 2026-10-05 12:01
 */
#include <cstdio>

typedef long long ll;

const int N = 10; // 题面固定 10×10 的网格

int grid[N][N];   // grid[r][c]：1 表示 *（墙），0 表示待判定的点
bool outside[N][N]; // outside[r][c]：该 0 格是否已被判定为外部

// 多源 BFS 洪水填充：从边界上的所有 0 格出发，把能走到的 0 格全部染成外部。
// 只穿过 0 格，遇到 1（墙）就停；曲线有缺口时洪水会漏进去，缺口自动被识别。
void bfs_fill() {
    int qx[N * N], qy[N * N]; // 队列存格子坐标，队列含义：待扩散的外部格
    int head = 0, tail = 0;

    // 种子：最外圈上的 0 格一定属于外部，全部入队
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            if (grid[r][c] == 0 && (r == 0 || r == N - 1 || c == 0 || c == N - 1)) {
                outside[r][c] = true;
                qx[tail] = r;
                qy[tail] = c;
                tail++;
            }

    while (head < tail) {
        int r = qx[head], c = qy[head];
        head++;
        int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 四方向相邻
        for (int k = 0; k < 4; k++) {
            int nr = r + dir[k][0], nc = c + dir[k][1];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue; // 越界
            if (grid[nr][nc] == 0 && !outside[nr][nc]) {
                outside[nr][nc] = true;
                qx[tail] = nr;
                qy[tail] = nc;
                tail++;
            }
        }
    }
}

int main() {
    // 按行优先读扁平整数：真实数据里有测例只有 9 行，缺的位置保持 0，不影响答案
    for (int i = 0; i < N * N; i++)
        scanf("%d", &grid[i / N][i % N]);

    bfs_fill();

    // 剩下没被染成外部的 0 格，就是被 * 围住的内部点，个数即面积
    int ans = 0;
    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++)
            if (grid[r][c] == 0 && !outside[r][c])
                ans++;

    printf("%d\n", ans);
    return 0;
}
