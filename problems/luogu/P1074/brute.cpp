#include <bits/stdc++.h>
using namespace std;

// brute.cpp：更直观的朴素回溯版。
// 按固定顺序找下一个空格，再枚举能填的数字。
// 它不做“最少候选优先”的格子选择，因此搜索树更大，
// 但逻辑非常直接，适合帮助理解数独回溯的基本过程。

int board[9][9];
int row_mask[9], col_mask[9], box_mask[9];
int blanks[81][2];
int blank_cnt;
int best_score = -1;
int current_score = 0;

int weight_value[9][9] = {
    {6, 6, 6, 6, 6, 6, 6, 6, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 9, 10, 9, 8, 7, 6},
    {6, 7, 8, 9, 9, 9, 8, 7, 6},
    {6, 7, 8, 8, 8, 8, 8, 7, 6},
    {6, 7, 7, 7, 7, 7, 7, 7, 6},
    {6, 6, 6, 6, 6, 6, 6, 6, 6}
};

int get_box_id(int x, int y) {
    return (x / 3) * 3 + (y / 3);
}

void dfs(int idx) {
    if (idx == blank_cnt) {
        if (current_score > best_score) {
            best_score = current_score;
        }
        return;
    }

    int x = blanks[idx][0];
    int y = blanks[idx][1];
    int box_id = get_box_id(x, y);

    for (int digit = 1; digit <= 9; digit++) {
        int bit = 1 << (digit - 1);
        if ((row_mask[x] & bit) || (col_mask[y] & bit) || (box_mask[box_id] & bit)) {
            continue;
        }

        board[x][y] = digit;
        row_mask[x] |= bit;
        col_mask[y] |= bit;
        box_mask[box_id] |= bit;
        current_score += digit * weight_value[x][y];

        dfs(idx + 1);

        current_score -= digit * weight_value[x][y];
        box_mask[box_id] ^= bit;
        col_mask[y] ^= bit;
        row_mask[x] ^= bit;
        board[x][y] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(row_mask, 0, sizeof(row_mask));
    memset(col_mask, 0, sizeof(col_mask));
    memset(box_mask, 0, sizeof(box_mask));

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> board[i][j];
            if (board[i][j] == 0) {
                blanks[blank_cnt][0] = i;
                blanks[blank_cnt][1] = j;
                blank_cnt++;
                continue;
            }

            int digit = board[i][j];
            int bit = 1 << (digit - 1);
            int box_id = get_box_id(i, j);
            if ((row_mask[i] & bit) || (col_mask[j] & bit) || (box_mask[box_id] & bit)) {
                cout << -1 << '\n';
                return 0;
            }
            row_mask[i] |= bit;
            col_mask[j] |= bit;
            box_mask[box_id] |= bit;
            current_score += digit * weight_value[i][j];
        }
    }

    dfs(0);
    cout << best_score << '\n';

    return 0;
}
