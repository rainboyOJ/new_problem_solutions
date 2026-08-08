#include <bits/stdc++.h>
using namespace std;

const int FULL_MASK = (1 << 9) - 1;

char h_rel[9][8];
char v_rel[8][9];

int board[9][9];
int row_mask[9], col_mask[9], box_mask[9];

int get_box_id(int x, int y) {
    return (x / 3) * 3 + (y / 3);
}

int bit_count(int x) {
    return __builtin_popcount((unsigned int)x);
}

int lowbit_to_digit(int bit) {
    for (int d = 1; d <= 9; d++) {
        if (bit == (1 << (d - 1))) {
            return d;
        }
    }
    return 0;
}

int get_candidate_mask(int x, int y) {
    int used = row_mask[x] | col_mask[y] | box_mask[get_box_id(x, y)];
    int mask = FULL_MASK ^ used;

    // 根据左右不等式删掉不可能的数字。
    if (y < 8 && h_rel[x][y] != 0 && board[x][y + 1] != 0) {
        int right_val = board[x][y + 1];
        int new_mask = 0;
        for (int d = 1; d <= 9; d++) {
            if ((mask & (1 << (d - 1))) == 0) {
                continue;
            }
            if ((h_rel[x][y] == '<' && d < right_val) || (h_rel[x][y] == '>' && d > right_val)) {
                new_mask |= 1 << (d - 1);
            }
        }
        mask = new_mask;
    }
    if (y > 0 && h_rel[x][y - 1] != 0 && board[x][y - 1] != 0) {
        int left_val = board[x][y - 1];
        int new_mask = 0;
        for (int d = 1; d <= 9; d++) {
            if ((mask & (1 << (d - 1))) == 0) {
                continue;
            }
            if ((h_rel[x][y - 1] == '<' && left_val < d) || (h_rel[x][y - 1] == '>' && left_val > d)) {
                new_mask |= 1 << (d - 1);
            }
        }
        mask = new_mask;
    }

    // 根据上下不等式删掉不可能的数字。
    if (x < 8 && v_rel[x][y] != 0 && board[x + 1][y] != 0) {
        int down_val = board[x + 1][y];
        int new_mask = 0;
        for (int d = 1; d <= 9; d++) {
            if ((mask & (1 << (d - 1))) == 0) {
                continue;
            }
            if ((v_rel[x][y] == '^' && d < down_val) || (v_rel[x][y] == 'v' && d > down_val)) {
                new_mask |= 1 << (d - 1);
            }
        }
        mask = new_mask;
    }
    if (x > 0 && v_rel[x - 1][y] != 0 && board[x - 1][y] != 0) {
        int up_val = board[x - 1][y];
        int new_mask = 0;
        for (int d = 1; d <= 9; d++) {
            if ((mask & (1 << (d - 1))) == 0) {
                continue;
            }
            if ((v_rel[x - 1][y] == '^' && up_val < d) || (v_rel[x - 1][y] == 'v' && up_val > d)) {
                new_mask |= 1 << (d - 1);
            }
        }
        mask = new_mask;
    }

    return mask;
}

bool dfs() {
    int best_x = -1;
    int best_y = -1;
    int best_mask = 0;
    int best_cnt = 10;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] != 0) {
                continue;
            }
            int mask = get_candidate_mask(i, j);
            int cnt = bit_count(mask);
            if (cnt == 0) {
                return false;
            }
            if (cnt < best_cnt) {
                best_cnt = cnt;
                best_x = i;
                best_y = j;
                best_mask = mask;
            }
        }
    }

    if (best_x == -1) {
        return true;
    }

    while (best_mask != 0) {
        int lowbit = best_mask & (-best_mask);
        best_mask -= lowbit;
        int digit = lowbit_to_digit(lowbit);
        int box_id = get_box_id(best_x, best_y);

        board[best_x][best_y] = digit;
        row_mask[best_x] |= lowbit;
        col_mask[best_y] |= lowbit;
        box_mask[box_id] |= lowbit;

        if (dfs()) {
            return true;
        }

        box_mask[box_id] ^= lowbit;
        col_mask[best_y] ^= lowbit;
        row_mask[best_x] ^= lowbit;
        board[best_x][best_y] = 0;
    }

    return false;
}

void read_relations() {
    vector<string> lines;
    string line;
    while ((int)lines.size() < 15 && getline(cin, line)) {
        if (line.empty()) {
            continue;
        }
        lines.push_back(line);
    }

    memset(h_rel, 0, sizeof(h_rel));
    memset(v_rel, 0, sizeof(v_rel));

    for (int idx = 0; idx < 15; idx++) {
        vector<char> arr;
        for (int i = 0; i < (int)lines[idx].size(); i++) {
            char ch = lines[idx][i];
            if (ch == '<' || ch == '>' || ch == '^' || ch == 'v') {
                arr.push_back(ch);
            }
        }
        if ((int)arr.size() == 6) {
            int row = (idx / 5) * 3 + ((idx % 5) / 2);
            int cols[6] = {0, 1, 3, 4, 6, 7};
            for (int i = 0; i < 6; i++) {
                h_rel[row][cols[i]] = arr[i];
            }
        } else {
            int row = (idx / 5) * 3 + ((idx % 5 - 1) / 2);
            for (int i = 0; i < 9; i++) {
                v_rel[row][i] = arr[i];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    memset(board, 0, sizeof(board));
    memset(row_mask, 0, sizeof(row_mask));
    memset(col_mask, 0, sizeof(col_mask));
    memset(box_mask, 0, sizeof(box_mask));

    read_relations();

    dfs();

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j) {
                cout << ' ';
            }
            cout << board[i][j];
        }
        cout << '\n';
    }
    return 0;
}
