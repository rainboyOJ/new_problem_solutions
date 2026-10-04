/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 21:00
 * update_at: 2026-10-04 21:00
 */
// main.cpp：三维迷宫 BFS 求 S 到 E 的最少分钟数；六方向（层±1 / 行±1 / 列±1）扩展。

#include <iostream>
#include <queue>
#include <string>
using namespace std;

typedef long long ll;

const int MAXL = 35; // L、R、C 都不超过 30，留一点冗余
const int MAXR = 35;
const int MAXC = 35;

char dungeon[MAXL][MAXR][MAXC]; // 三维网格，存原字符 '#' '.' 'S' 'E'

// 六个方向的 (层, 行, 列) 偏移：层 ±1 是上下，行 ±1 是前后，列 ±1 是左右
int dl[6] = { 1, -1, 0, 0, 0, 0 };
int dr[6] = { 0, 0, 1, -1, 0, 0 };
int dc[6] = { 0, 0, 0, 0, 1, -1 };

bool seen[MAXL][MAXR][MAXC]; // BFS 入队即标记，保证每格只展开一次

struct Pos {
    int l, r, c;
};

// 六方向 BFS：返回 start 到 target 的最少分钟数；不可达返回 -1
int bfs(int L, int R, int C, Pos start, Pos target) {
    queue<Pos> q;
    q.push(start);
    seen[start.l][start.r][start.c] = true;

    int minutes = 0;
    while (!q.empty()) {
        int sz = (int)q.size(); // 当前层（恰好 minutes 分钟可达）的格子数
        for (int i = 0; i < sz; i++) {
            Pos cur = q.front(); q.pop();
            if (cur.l == target.l && cur.r == target.r && cur.c == target.c) {
                return minutes;
            }
            for (int k = 0; k < 6; k++) {
                int nl = cur.l + dl[k];
                int nr = cur.r + dr[k];
                int nc = cur.c + dc[k];
                // 先判界，再判墙，再判未访问
                if (nl < 0 || nl >= L || nr < 0 || nr >= R || nc < 0 || nc >= C) continue;
                if (dungeon[nl][nr][nc] == '#') continue;
                if (seen[nl][nr][nc]) continue;
                seen[nl][nr][nc] = true; // 入队即标记
                q.push({nl, nr, nc});
            }
        }
        minutes++;
    }
    return -1; // S 与 E 不连通
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, R, C;
    while (cin >> L >> R >> C) {
        if (L == 0 && R == 0 && C == 0) break;

        Pos start{-1, -1, -1}, target{-1, -1, -1};
        for (int l = 0; l < L; l++) {
            for (int r = 0; r < R; r++) {
                string row;
                cin >> row;
                for (int c = 0; c < C; c++) {
                    dungeon[l][r][c] = row[c];
                    if (row[c] == 'S') start = {l, r, c};
                    else if (row[c] == 'E') target = {l, r, c};
                }
            }
        }

        // 每组数据前清空 seen 数组实际用到的范围（L、R、C 都 ≤ 30）
        for (int l = 0; l < L; l++)
            for (int r = 0; r < R; r++)
                for (int c = 0; c < C; c++)
                    seen[l][r][c] = false;

        int ans = bfs(L, R, C, start, target);
        if (ans >= 0) cout << "Escaped in " << ans << " minute(s)." << '\n';
        else cout << "Trapped!" << '\n';
    }

    return 0;
}
