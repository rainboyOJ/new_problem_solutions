/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:48
 */
#include <bits/stdc++.h>
using namespace std;

const int ROWS = 15;
const int COLS = 10;

int board[ROWS][COLS]; // 方格图，1 表示该格已有方块
int block[4][4];       // 下落板块图案，1 表示该格有方块

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cin >> board[i][j];
        }
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cin >> block[i][j];
        }
    }

    int start_column;
    cin >> start_column;
    start_column--; // 输入列号从 1 开始，转为 0 基下标

    // 从第 0 行开始，每次试探下移一行：板块所有实心格都要仍能放下。
    int top = 0;
    while (true) {
        bool can_fall = true;
        for (int i = 0; i < 4 && can_fall; i++) {
            for (int j = 0; j < 4; j++) {
                if (block[i][j] == 0) {
                    continue;
                }
                int row = top + 1 + i;
                int column = start_column + j;
                // 下移一行后越界，或与已有方块重叠，都不能再下落
                if (row >= ROWS || board[row][column]) {
                    can_fall = false;
                    break;
                }
            }
        }
        if (!can_fall) {
            break;
        }
        top++;
    }

    // 把板块写入最终落定位置
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (block[i][j]) {
                board[top + i][start_column + j] = 1;
            }
        }
    }

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (j > 0) {
                cout << ' ';
            }
            cout << board[i][j];
        }
        cout << '\n';
    }
    return 0;
}