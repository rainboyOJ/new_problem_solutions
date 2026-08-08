/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

// 北、东、南、西
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

char grid[10][11]; // 10x10 网格

// 状态总数：10*10*4 * 10*10*4 = 160000
bool vis[10][10][4][10][10][4];

// 尝试往当前方向走一步，如果被阻挡则转向
void move(int &r, int &c, int &dir) {
    int nr = r + dr[dir];
    int nc = c + dc[dir];
    // 越界或障碍物
    if (nr < 0 || nr >= 10 || nc < 0 || nc >= 10 || grid[nr][nc] == '*') {
        dir = (dir + 1) % 4; // 顺时针转 90 度
    } else {
        r = nr;
        c = nc;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 读入网格
    for (int i = 0; i < 10; i++) cin >> grid[i];

    int cr = 0, cc = 0, fr = 0, fc = 0; // 牛和 Farmer 的坐标
    // 找初始位置
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (grid[i][j] == 'C') { cr = i; cc = j; }
            if (grid[i][j] == 'F') { fr = i; fc = j; }
        }
    }

    int cd = 0, fd = 0; // 初始都朝北(0)
    int minutes = 0;

    while (1) {
        // 检查状态是否重复
        if (vis[cr][cc][cd][fr][fc][fd]) {
            cout << 0 << "\n";
            return 0;
        }
        vis[cr][cc][cd][fr][fc][fd] = true;

        // 牛和 Farmer 各走一步
        move(cr, cc, cd);
        move(fr, fc, fd);
        minutes++;

        // 相遇
        if (cr == fr && cc == fc) {
            cout << minutes << "\n";
            return 0;
        }
    }

    return 0;
}
