/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:42
 * update_at: 2026-10-05 05:42
 */

// 红与黑：从 @ 出发做一次洪水填充，统计起点所在连通分量的黑砖数（含起点）。
#include <cstdio>

typedef long long ll;

const int MAXN = 25;
const int DIRS[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // 上、下、左、右四个相邻方向

char grid[MAXN][MAXN]; // 网格，已访问的黑砖就地染色成 '#'，不需要额外的 visited 数组
ll stack_r[MAXN * MAXN]; // 待展开格子的行坐标
ll stack_c[MAXN * MAXN]; // 待展开格子的列坐标

// 从 (sr, sc) 出发洪水填充，返回能到达的黑砖数（包含起点）
ll flood_fill(ll h, ll w, ll sr, ll sc) {
    ll top = 0;
    stack_r[top] = sr;
    stack_c[top] = sc;
    top++;
    grid[sr][sc] = '#'; // 入栈即染色，保证同一个点不会被重复压栈

    ll count = 0;
    while (top > 0) {
        top--;
        ll r = stack_r[top];
        ll c = stack_c[top];
        count++; // 弹出即计数，每个可达黑砖恰好出栈一次
        for (ll d = 0; d < 4; d++) {
            ll nr = r + DIRS[d][0];
            ll nc = c + DIRS[d][1];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue; // 越界
            if (grid[nr][nc] != '.') continue; // 不是可走的黑砖
            grid[nr][nc] = '#';
            stack_r[top] = nr;
            stack_c[top] = nc;
            top++;
        }
    }
    return count;
}

int main() {
    while (1) {
        ll w, h;
        scanf("%lld %lld", &w, &h);
        if (w == 0 && h == 0) break; // 一行读入两个零表示输入结束

        ll sr = -1, sc = -1; // 起点 @ 的坐标，每个数据集合中唯一出现一次
        for (ll r = 0; r < h; r++) {
            scanf("%s", grid[r]);
            for (ll c = 0; c < w; c++) {
                if (grid[r][c] == '@') {
                    sr = r;
                    sc = c;
                }
            }
        }

        printf("%lld\n", flood_fill(h, w, sr, sc));
    }
    return 0;
}
