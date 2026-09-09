/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-28 21:28
 * update_at: 2026-08-28 21:28
 */
// main.cpp：B. Treasure（藏宝图）最终解。
// 从每个格子出发，沿 8 个方向搜索单词；用一个标记记录是否已经转过一次 90 度弯。
// 每个格子作为起点、每个方向作为初始方向，天然保证同一种摆放只被计数一次。
#include <bits/stdc++.h>
using namespace std;

const int MAXRC = 105;

string w;                 // 要找的单词 W（由不同大写字母组成）
int R, C;                 // 网格行数、列数
char g[MAXRC][MAXRC];     // 网格
int ans = 0;

// 8 个方向：0 上，1 右上，2 右，3 右下，4 下，5 左下，6 左，7 左上
// 在这个编号下，hd + 2 和 hd + 6（对 8 取模）恰好是两个垂直方向
int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

// 已经匹配了 w[0..pos-1]，当前停在 (x,y)，前进方向是 hd，turned 表示是否转过弯。
// 下一步尝试把 w[pos] 放到下一个格子里：要么继续直走，要么（在还没转过弯时）转 90 度。
void dfs(int pos, int x, int y, int hd, bool turned) {
    if (pos == (int)w.size()) {   // 整条路径的字母全部匹配成功
        ans++;
        return;
    }

    // 不转弯：继续沿 hd 方向走到下一个格子
    int nx = x + dx[hd];
    int ny = y + dy[hd];
    if (nx >= 0 && nx < R && ny >= 0 && ny < C && g[nx][ny] == w[pos]) {
        dfs(pos + 1, nx, ny, hd, turned);
    }

    // 转弯：90 度直角拐弯只能发生一次，且第一段至少要有 2 个字母
    //（pos >= 2 表示当前格子是 w[pos-1]，即拐点不在起点上）
    if (pos >= 2 && !turned) {
        for (int d = 2; d <= 6; d += 4) {       // 左转 d=6，右转 d=2，两个垂直方向
            int hd2 = (hd + d) % 8;
            int tx = x + dx[hd2];
            int ty = y + dy[hd2];
            if (tx >= 0 && tx < R && ty >= 0 && ty < C && g[tx][ty] == w[pos]) {
                dfs(pos + 1, tx, ty, hd2, true);
            }
        }
    }
}

void solve() {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (g[i][j] != w[0]) {
                continue;
            }
            // 从起点 (i,j) 分别向 8 个方向开始匹配
            for (int hd = 0; hd < 8; hd++) {
                dfs(1, i, j, hd, false);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> w >> R >> C;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> g[i][j];
        }
    }

    solve();
    cout << ans << '\n';
    return 0;
}
