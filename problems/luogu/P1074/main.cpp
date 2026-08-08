#include <bits/stdc++.h>
using namespace std;

int board[9][9];
int row_mask[9], col_mask[9], box_mask[9];
int empty_cnt;
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

int cell_weight[81];

int get_box_id(int x, int y) {
    return (x / 3) * 3 + (y / 3);
}

int bit_count(int x) {
    return __builtin_popcount((unsigned int)x);
}

// 取最低位 1 对应的数字编号，返回 1..9。
int bit_to_digit(int bit) {
    for (int d = 1; d <= 9; d++) {
        if (bit == (1 << (d - 1))) {
            return d;
        }
    }
    return 0;
}

int get_candidate_mask(int x, int y) {
    int used = row_mask[x] | col_mask[y] | box_mask[get_box_id(x, y)];
    return ((1 << 9) - 1) ^ used;
}

void dfs(int remain) {
    if (remain == 0) {
        if (current_score > best_score) {
            best_score = current_score;
        }
        return;
    }

    int best_x = -1;
    int best_y = -1;
    int best_mask = 0;
    int best_cnt = 10;

    // 选择候选数字最少的空格，减少分支数。
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] != 0) {
                continue;
            }
            int mask = get_candidate_mask(i, j);
            int cnt = bit_count(mask);
            if (cnt == 0) {
                return;
            }
            if (cnt < best_cnt) {
                best_cnt = cnt;
                best_x = i;
                best_y = j;
                best_mask = mask;
                if (cnt == 1) {
                    break;
                }
            }
        }
        if (best_cnt == 1) {
            break;
        }
    }

    int pos = best_x * 9 + best_y;

    while (best_mask != 0) {
        int lowbit = best_mask & (-best_mask);
        best_mask -= lowbit;

        int digit = bit_to_digit(lowbit);
        int box_id = get_box_id(best_x, best_y);

        board[best_x][best_y] = digit;
        row_mask[best_x] |= lowbit;
        col_mask[best_y] |= lowbit;
        box_mask[box_id] |= lowbit;
        current_score += digit * cell_weight[pos];

        dfs(remain - 1);

        current_score -= digit * cell_weight[pos];
        box_mask[box_id] ^= lowbit;
        col_mask[best_y] ^= lowbit;
        row_mask[best_x] ^= lowbit;
        board[best_x][best_y] = 0;
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
            cell_weight[i * 9 + j] = weight_value[i][j];
        }
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> board[i][j];
            if (board[i][j] == 0) {
                empty_cnt++;
                continue;
            }

            int digit = board[i][j];
            int bit = 1 << (digit - 1);
            int box_id = get_box_id(i, j);

            // 如果初始盘面本身已经冲突，直接无解。
            if ((row_mask[i] & bit) || (col_mask[j] & bit) || (box_mask[box_id] & bit)) {
                cout << -1 << '\n';
                return 0;
            }

            row_mask[i] |= bit;
            col_mask[j] |= bit;
            box_mask[box_id] |= bit;
            current_score += digit * cell_weight[i * 9 + j];
        }
    }

    dfs(empty_cnt);
    cout << best_score << '\n';

    return 0;
}
