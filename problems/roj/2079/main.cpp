/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:38
 * update_at: 2026-10-06 10:38
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 130;

int N, B;
char blocked[MAXN][MAXN]; // blocked[row][col] = 1 表示该格是路障
char trail[MAXN][MAXN];   // 当前这条路线已经走过的格子

// 四个方向的行列偏移：北、东、南、西
int DR[4] = {-1, 0, 1, 0};
int DC[4] = {0, 1, 0, -1};

const int UNDO = 0; // 栈帧类型：回退帧，撤销一段直行留下的足迹
const int WALK = 1; // 栈帧类型：直行帧，从 (row, col) 沿 dir 直行到底

// 一行直行是一个栈帧；用显式栈代替深递归，避免路线太长时爆栈
struct Frame {
    int type;
    int row;
    int col;
    int dir;
    int run_len; // 回退帧需要撤销的格子数
};

int count_cells; // 当前路线已经走过的格子数
int answer;      // 目前为止能走过的最多格子数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> B;

    // 路障坐标形如 E2：字母是列（A 起），数字是行（1 起）
    for (int i = 0; i < B; i++) {
        string pos;
        cin >> pos;
        int col = pos[0] - 'A';
        int row = 0;
        int len = pos.size();
        for (int j = 1; j < len; j++) {
            row = row * 10 + (pos[j] - '0');
        }
        blocked[row - 1][col] = 1;
    }

    trail[0][0] = 1;
    count_cells = 1;
    answer = 1;

    vector<Frame> stk;
    // 起步只能向右（东）或向下（南）
    stk.push_back(Frame{WALK, 0, 0, 1, 0});
    stk.push_back(Frame{WALK, 0, 0, 2, 0});

    while (!stk.empty()) {
        Frame f = stk.back();
        stk.pop_back();

        if (f.type == UNDO) {
            // 撤销这一段直行的足迹：从起点沿原方向走 run_len 格逐格清空
            int r = f.row;
            int c = f.col;
            for (int k = 0; k < f.run_len; k++) {
                r += DR[f.dir];
                c += DC[f.dir];
                trail[r][c] = 0;
            }
            count_cells -= f.run_len;
            continue;
        }

        int r = f.row;
        int c = f.col;
        int d = f.dir;
        int run_len = 0;
        int hit_trail = 0; // 撞上自己的足迹：题目规定此时整段散步结束，不再转弯
        // 选定方向后一直走，直到棋盘边缘、路障或自己的足迹
        while (true) {
            int nr = r + DR[d];
            int nc = c + DC[d];
            if (nr < 0 || nr >= N || nc < 0 || nc >= N) break;
            if (blocked[nr][nc]) break;
            if (trail[nr][nc]) {
                hit_trail = 1;
                break;
            }
            trail[nr][nc] = 1;
            run_len++;
            r = nr;
            c = nc;
        }
        count_cells += run_len;
        if (count_cells > answer) answer = count_cells;

        // 先压入回退帧，等这棵子树的兄弟分支都跑完，再统一撤销本段足迹
        stk.push_back(Frame{UNDO, f.row, f.col, d, run_len});

        if (hit_trail) continue; // 撞到自己的足迹，无路可走，直接回溯

        // 只有撞边缘或路障才转弯：左转、右转都试，第一步走得通才入栈
        int nd = (d + 1) % 4;
        int nr = r + DR[nd];
        int nc = c + DC[nd];
        if (nr >= 0 && nr < N && nc >= 0 && nc < N && !blocked[nr][nc] && !trail[nr][nc]) {
            stk.push_back(Frame{WALK, r, c, nd, 0});
        }
        nd = (d + 3) % 4;
        nr = r + DR[nd];
        nc = c + DC[nd];
        if (nr >= 0 && nr < N && nc >= 0 && nc < N && !blocked[nr][nc] && !trail[nr][nc]) {
            stk.push_back(Frame{WALK, r, c, nd, 0});
        }
    }

    cout << answer << endl;

    return 0;
}
