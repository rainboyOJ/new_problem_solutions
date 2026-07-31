/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:05
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int board[15][10], block[4][4];
    for (int i = 0; i < 15; i++) for (int j = 0; j < 10; j++) cin >> board[i][j];
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) cin >> block[i][j];
    int left;
    cin >> left;
    left--;
    int top = 0;
    while (true) {
        bool can_fall = true;
        for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) {
            if (block[i][j] == 0) continue;
            int row = top + 1 + i, column = left + j;
            if (row >= 15 || board[row][column]) can_fall = false;
        }
        if (!can_fall) break;
        top++;
    }
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) if (block[i][j]) board[top + i][left + j] = 1;
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 10; j++) cout << (j ? " " : "") << board[i][j];
        cout << '\n';
    }
    return 0;
}
