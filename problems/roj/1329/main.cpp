/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:02
 * update_at: 2026-10-05 10:02
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 105; // 行数上限
const int MAXM = 105; // 列数上限

int n, m;
char a[MAXN][MAXM]; // a[r][c]：第 r 行第 c 列的字符，'0' 表示背景，'1'~'9' 是细胞数字
int q[MAXN * MAXM][2]; // BFS 队列，q[i][0]=行，q[i][1]=列；每格至多入队一次
int dr[4] = {-1, 1, 0, 0}; // 四个方向的行偏移
int dc[4] = {0, 0, -1, 1}; // 四个方向的列偏移

// 从 (sr, sc) 出发，把这个四连通细胞全部原地抹成 '0'（省掉 visited 数组）
void flood_fill(int sr, int sc) {
    int head = 0, tail = 0;
    a[sr][sc] = '0';
    q[tail][0] = sr;
    q[tail][1] = sc;
    tail++;
    while (head < tail) {
        int r = q[head][0];
        int c = q[head][1];
        head++;
        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];
            if (nr < 0 || nr >= n || nc < 0 || nc >= m)
                continue;
            if (a[nr][nc] == '0')
                continue;
            a[nr][nc] = '0'; // 入队即标记，保证每格至多入队一次
            q[tail][0] = nr;
            q[tail][1] = nc;
            tail++;
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int r = 0; r < n; r++)
        scanf("%s", a[r]);

    int cells = 0;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            if (a[r][c] != '0') { // 还没抹掉的细胞数字 = 一个新细胞的种子
                cells++;
                flood_fill(r, c);
            }
        }
    }

    printf("%d\n", cells);
    return 0;
}
