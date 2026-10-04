/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:16
 * update_at: 2026-10-05 02:16
 */

#include <cstdio>

typedef long long ll;

const int ALL_DIGITS = 0x3FE; // 二进制第 1~9 位表示数字 1~9 可用

// 全局数据
int grid[9][9];       // 当前棋盘，0 表示未填
int row_mask[9];      // row_mask[r]：第 r 行已填数字的位掩码
int col_mask[9];      // col_mask[c]：第 c 列已填数字的位掩码
int box_mask[9];      // box_mask[b]：第 b 宫已填数字的位掩码
int emp_r[81];        // 空格的行号列表
int emp_c[81];        // 空格的列号列表
int emp_cnt = 0;      // 空格总数
int filled_cnt = 0;   // 已填的空格数
ll max_score = -1;    // 当前搜到的最高得分，初始 -1 表示无解

// 计算第 r 行第 c 列的靶形权重（6~10 分）
inline int get_weight(int r, int c) {
    int t = r;
    if (8 - r < t) t = 8 - r;
    if (c < t) t = c;
    if (8 - c < t) t = 8 - c;
    return 6 + t;
}

// 统计掩码中置位个数
inline int bit_count(int x) {
    int cnt = 0;
    while (x) {
        x &= x - 1;
        cnt++;
    }
    return cnt;
}

// 取出掩码最低位的 1（即最小候选数字对应的位）
inline int lowbit(int x) {
    return x & -x;
}

// MRV 搜索：每层在所有空格中选候选数最少的格子展开
// score：当前已确定的得分；无解时保持 max_score = -1
void dfs(ll score) {
    // 候选数最少的空格
    int best_i = -1;
    int min_choices = 10;
    int best_mask = 0;

    // 遍历所有空格，找候选数最少的那个
    for (int i = 0; i < emp_cnt; i++) {
        if (grid[emp_r[i]][emp_c[i]] != 0) continue; // 已填的空格跳过
        int r = emp_r[i];
        int c = emp_c[i];
        int b = (r / 3) * 3 + c / 3;
        // 可填数字集合 = 全集 去掉 行、列、宫已用数字
        int avail = ALL_DIGITS & ~(row_mask[r] | col_mask[c] | box_mask[b]);
        int cnt = bit_count(avail);
        if (cnt == 0) return;      // 有格子无数可填，当前分支必无解，剪枝
        if (cnt < min_choices) {   // MRV：挑分支最少的空格
            min_choices = cnt;
            best_i = i;
            best_mask = avail;
            if (cnt == 1) break;   // 唯一候选数，不用再找了
        }
    }

    // 没有空格可填：得到一个完整解，更新最高分
    if (best_i == -1) {
        if (score > max_score) max_score = score;
        return;
    }

    int r = emp_r[best_i];
    int c = emp_c[best_i];
    int b = (r / 3) * 3 + c / 3;
    int w = get_weight(r, c);

    // 依次尝试该格子的每个候选数字，回溯复原
    int mask = best_mask;
    while (mask) {
        int lsb = lowbit(mask);
        mask ^= lsb;
        int d = 0;
        for (int k = lsb; k > 1; k >>= 1) d++; // lsb 对应的数字

        grid[r][c] = d;
        row_mask[r] |= lsb;
        col_mask[c] |= lsb;
        box_mask[b] |= lsb;

        dfs(score + (ll)d * w);

        grid[r][c] = 0;
        row_mask[r] ^= lsb;
        col_mask[c] ^= lsb;
        box_mask[b] ^= lsb;
    }
}

int main() {
    // 读入数独，初始化掩码、得分和空格列表
    ll init_score = 0;
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            int v;
            scanf("%d", &v);
            grid[r][c] = v;
            int b = (r / 3) * 3 + c / 3;
            if (v != 0) {
                int bit = 1 << v;
                // 同一行、列、宫出现重复数字，直接无解
                if (row_mask[r] & bit || col_mask[c] & bit || box_mask[b] & bit) {
                    printf("-1\n");
                    return 0;
                }
                row_mask[r] |= bit;
                col_mask[c] |= bit;
                box_mask[b] |= bit;
                init_score += (ll)v * get_weight(r, c);
            } else {
                emp_r[emp_cnt] = r;
                emp_c[emp_cnt] = c;
                emp_cnt++;
            }
        }
    }

    dfs(init_score);
    printf("%lld\n", max_score);
    return 0;
}
