/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-17 23:06
 */
#include <bits/stdc++.h>
using namespace std;

int z;                  // 加密方阵边长
int orientation;        // 当前整图旋转方向：0/1/2/3 分别表示 0/90/180/270 度
vector<string> picture; // 存储矩阵（以逻辑视图为准）

// 逻辑坐标 (row,col) 到存储坐标 (mapped_row,mapped_col) 的映射，随整图方向变化
void map_position(int row, int col, int &mapped_row, int &mapped_col) {
    if (orientation == 0) {
        mapped_row = row;
        mapped_col = col;
    } else if (orientation == 1) {
        mapped_row = z - 1 - col;
        mapped_col = row;
    } else if (orientation == 2) {
        mapped_row = z - 1 - row;
        mapped_col = z - 1 - col;
    } else {
        mapped_row = col;
        mapped_col = z - 1 - row;
    }
}

// 读取逻辑坐标 (row,col) 处的字符
char get_cell(int row, int col) {
    int mapped_row, mapped_col;
    map_position(row, col, mapped_row, mapped_col);
    return picture[mapped_row][mapped_col];
}

// 写入逻辑坐标 (row,col) 处的字符
void set_cell(int row, int col, char value) {
    int mapped_row, mapped_col;
    map_position(row, col, mapped_row, mapped_col);
    picture[mapped_row][mapped_col] = value;
}

// 撤销一次局部旋转：把 top,left 处边长 length 的正方形逆时针转回。
// 当前整图方向已提前由调用者更新，这里以逻辑视图操作即可
void undo_rotation(int top, int left, int length, int degree) {
    char old_value[10][10];
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            old_value[i][j] = get_cell(top + i, left + j);
        }
    }

    int times = degree / 90;
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < length; j++) {
            int old_row, old_col;
            if (times == 1) {
                old_row = j;
                old_col = length - 1 - i;
            } else if (times == 2) {
                old_row = length - 1 - i;
                old_col = length - 1 - j;
            } else {
                old_row = length - 1 - j;
                old_col = i;
            }
            set_cell(top + i, left + j, old_value[old_row][old_col]);
        }
    }
}

// 撤销一次局部翻转：direction=1 上下翻转，direction=-1 左右翻转。
// 翻转是自身的逆操作，直接反向搬回即可
void undo_flip(int top, int bottom, int left, int right, int direction) {
    int height = bottom - top + 1;
    int width = right - left + 1;
    char old_value[10][10];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            old_value[i][j] = get_cell(top + i, left + j);
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int old_row = direction == 1 ? height - 1 - i : i;
            int old_col = direction == -1 ? width - 1 - j : j;
            set_cell(top + i, left + j, old_value[old_row][old_col]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> z;
    picture.resize(z);
    for (int i = 0; i < z; i++) cin >> picture[i];
    int key_length;
    cin >> key_length;
    vector<int> key(key_length);
    for (int i = 0; i < key_length; i++) cin >> key[i];

    int operations = key[0];
    orientation = 0;
    for (int operation = operations - 1; operation >= 0; operation--) {
        int position = 1 + operation * 6;
        int type = key[position];
        if (type == 1) {
            int top = key[position + 1] - 1;
            int left = key[position + 2] - 1;
            int length = key[position + 3];
            int degree = key[position + 4];
            int whole_rotations = key[position + 5];
            orientation = (orientation + whole_rotations) % 4;
            undo_rotation(top, left, length, degree);
        } else {
            int top = key[position + 1] - 1;
            int bottom = key[position + 2] - 1;
            int left = key[position + 3] - 1;
            int right = key[position + 4] - 1;
            int direction = key[position + 5];
            undo_flip(top, bottom, left, right, direction);
        }
    }

    int last_row = -1;
    int last_col = -1;
    for (int i = 0; i < z; i++) {
        for (int j = 0; j < z; j++) {
            if (get_cell(i, j) != '?') {
                last_row = max(last_row, i);
                last_col = max(last_col, j);
            }
        }
    }
    cout << last_row + 1 << ' ' << last_col + 1 << '\n';
    for (int i = 0; i <= last_row; i++) {
        for (int j = 0; j <= last_col; j++) cout << get_cell(i, j);
        cout << '\n';
    }
    return 0;
}
