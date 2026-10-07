/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:17
 * update_at: 2026-10-06 09:17
 */

#include <cstdio>
#include <string>
using namespace std;

const int MAXN = 55;    // 网格最大 50 x 50，留一点余量
const int MAXROOM = 2600; // 最多 50*50 个房间，每个格子独立成一间

const int WEST = 1;   // 题面的墙编码：1 西 2 北 4 东 8 南
const int NORTH = 2;
const int EAST = 4;
const int SOUTH = 8;

int m, n;                     // m 为列数 M，n 为行数 N
int grid[MAXN][MAXN];         // grid[r][c] 是格子 (r,c) 的墙编码，行列均从 0 开始
int room[MAXN][MAXN];         // room[r][c] 是格子 (r,c) 所属的房间号，-1 表示未访问
int sizes[MAXROOM];           // sizes[i] 是第 i 间房的格子数，下标即房间号

int stack_y[MAXN * MAXN];     // 洪水填充的显式栈，避免蛇形大房间递归过深
int stack_x[MAXN * MAXN];

int room_cnt;                 // 房间总数

// 四个方向：偏移量与"这条边有墙"时对应的墙编码。
int dir_y[4] = {-1, 1, 0, 0};
int dir_x[4] = {0, 0, -1, 1};
int dir_wall[4] = {NORTH, SOUTH, WEST, EAST};

// 洪水填充：把整个网格划分成房间，同时统计每间房的格子数。
void label_rooms() {
    room_cnt = 0;
    for (int start = 0; start < n * m; start++) {
        int sr = start / m;
        int sc = start % m;
        if (room[sr][sc] >= 0) {
            continue;
        }
        int rid = room_cnt;
        room_cnt++;
        int top = 0;
        stack_y[top] = sr;
        stack_x[top] = sc;
        top++;
        room[sr][sc] = rid;
        int size = 0;
        while (top > 0) {
            top--;
            int y = stack_y[top];
            int x = stack_x[top];
            size++;
            int v = grid[y][x];
            // 顺着四条无墙的边扩散
            for (int d = 0; d < 4; d++) {
                if ((v & dir_wall[d]) != 0) {
                    continue; // 这条边有墙，走不过去
                }
                int ny = y + dir_y[d];
                int nx = x + dir_x[d];
                if (ny < 0 || ny >= n || nx < 0 || nx >= m) {
                    continue; // 邻居在城堡外
                }
                if (room[ny][nx] >= 0) {
                    continue; // 邻居已归属某间房
                }
                room[ny][nx] = rid;
                stack_y[top] = ny;
                stack_x[top] = nx;
                top++;
            }
        }
        sizes[rid] = size;
    }
}

int main() {
    scanf("%d%d", &m, &n);
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            scanf("%d", &grid[r][c]);
            room[r][c] = -1;
        }
    }

    label_rooms();

    // 洪水填充顺着无墙边扩散，所以相邻两格房间号不同就说明中间隔着墙。
    // 只需比较房间号，不必再查墙的编码。
    int best_merged = -1;
    int best_neg2x = 0;  // -2x 越大，墙的中点越靠西
    int best_y2 = -1;    // 2y 越大，墙的中点越靠南
    int best_r = 0;      // 输出用的行列号，从 1 开始
    int best_c = 0;
    char best_wall = 'E';

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            int here = room[r][c];
            // 拆竖墙：格 (r,c) 与 (r,c+1) 合并，题面用西侧格子命名，记 E
            if (c + 1 < m && room[r][c + 1] != here) {
                int other = room[r][c + 1];
                int merged = sizes[here] + sizes[other];
                int neg2x = -(2 * c + 2); // 中点横坐标 x = c+1
                int y2 = 2 * r + 1;       // 中点纵坐标 y = r+0.5
                if (merged > best_merged ||
                    (merged == best_merged && neg2x > best_neg2x) ||
                    (merged == best_merged && neg2x == best_neg2x && y2 > best_y2)) {
                    best_merged = merged;
                    best_neg2x = neg2x;
                    best_y2 = y2;
                    best_r = r + 1;
                    best_c = c + 1;
                    best_wall = 'E';
                }
            }
            // 拆横墙：格 (r,c) 与 (r+1,c) 合并，题面用南侧格子命名，记 N
            if (r + 1 < n && room[r + 1][c] != here) {
                int other = room[r + 1][c];
                int merged = sizes[here] + sizes[other];
                int neg2x = -(2 * c + 1); // 中点横坐标 x = c+0.5
                int y2 = 2 * r + 2;       // 中点纵坐标 y = r+1
                if (merged > best_merged ||
                    (merged == best_merged && neg2x > best_neg2x) ||
                    (merged == best_merged && neg2x == best_neg2x && y2 > best_y2)) {
                    best_merged = merged;
                    best_neg2x = neg2x;
                    best_y2 = y2;
                    best_r = r + 2;
                    best_c = c + 1;
                    best_wall = 'N';
                }
            }
        }
    }

    int max_size = 0;
    for (int i = 0; i < room_cnt; i++) {
        if (sizes[i] > max_size) {
            max_size = sizes[i];
        }
    }

    printf("%d\n", room_cnt);
    printf("%d\n", max_size);
    printf("%d\n", best_merged);
    printf("%d %d %c\n", best_r, best_c, best_wall);
    return 0;
}
