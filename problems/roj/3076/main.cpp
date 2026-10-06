/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 17:40
 * update_at: 2026-10-06 17:40
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int FULL = 0b1111111110; // 数字 1..9 各占一位，第 0 位空着

int weight[81];          // 每格的分值
int row_of[81];          // 空格编号 -> 行
int col_of[81];          // 空格编号 -> 列
int box_of[81];          // 空格编号 -> 宫
int w_of[81];            // 空格编号 -> 分值
int rows[9], cols[9], boxes[9]; // 行/列/宫的已用数字位掩码
int blanks[81];          // 空格的一维下标
int blank_cnt;           // 空格数量
ll best;                 // 当前最优总分
ll gain;                 // 已知数字的固定分数

// 上界：每个空格都填自己候选里的最大数字，若仍不超 best 则剪枝
inline ll upper_bound(int *alive, int alive_cnt) {
    ll cap = 0;
    for (int i = 0; i < alive_cnt; ++i) {
        int pos = alive[i];
        int cands = FULL & ~(rows[row_of[pos]] | cols[col_of[pos]] | boxes[box_of[pos]]);
        if (cands == 0) return 0; // 无候选，这条分支已死
        int max_d = 31 - __builtin_clz(cands); // 最高位的 1 对应的数字
        cap += (ll)max_d * w_of[pos];
    }
    return cap;
}

void dfs(ll score, ll rest, int *alive, int alive_cnt) {
    if (alive_cnt == 0) { // 所有空格填完，得到完整解
        if (score > best) best = score;
        return;
    }
    // 上界剪枝
    ll cap = upper_bound(alive, alive_cnt);
    if (score + cap <= best) return;

    // MRV：找候选最少的空格
    int min_cands = 10;
    int chosen_idx = -1;
    int chosen_cands = 0;
    for (int i = 0; i < alive_cnt; ++i) {
        int pos = alive[i];
        int cands = FULL & ~(rows[row_of[pos]] | cols[col_of[pos]] | boxes[box_of[pos]]);
        int cnt = __builtin_popcount(cands);
        if (cnt < min_cands) {
            min_cands = cnt;
            chosen_idx = i;
            chosen_cands = cands;
            if (cnt == 1) break; // 不可能更少
        }
    }

    int pos = alive[chosen_idx];
    // 把选中的空格从 alive 中移除（与最后一个交换）
    alive[chosen_idx] = alive[alive_cnt - 1];

    // 从大到小枚举候选数字
    while (chosen_cands) {
        // 取当前候选集合里的最大数字（最高位）
        int d = 31 - __builtin_clz(chosen_cands);
        int use_bit = 1 << d;
        chosen_cands ^= use_bit;

        rows[row_of[pos]] |= use_bit;
        cols[col_of[pos]] |= use_bit;
        boxes[box_of[pos]] |= use_bit;

        dfs(score + (ll)d * w_of[pos], rest - w_of[pos], alive, alive_cnt - 1);

        rows[row_of[pos]] ^= use_bit;
        cols[col_of[pos]] ^= use_bit;
        boxes[box_of[pos]] ^= use_bit;
    }

    // 恢复 alive 数组
    alive[chosen_idx] = pos;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 预计算分值表：按到中心的切比雪夫距离分层
    for (int i = 0; i < 81; ++i) {
        int r = i / 9, c = i % 9;
        int d = max(abs(r - 4), abs(c - 4));
        weight[i] = 10 - d; // d=0->10, d=1->9, ..., d=4->6
    }

    gain = 0;
    blank_cnt = 0;
    memset(rows, 0, sizeof(rows));
    memset(cols, 0, sizeof(cols));
    memset(boxes, 0, sizeof(boxes));

    for (int i = 0; i < 81; ++i) {
        int x;
        cin >> x;
        if (x == 0) {
            blanks[blank_cnt++] = i;
        } else {
            int bit = 1 << x;
            int r = i / 9, c = i % 9;
            rows[r] |= bit;
            cols[c] |= bit;
            boxes[r / 3 * 3 + c / 3] |= bit;
            gain += (ll)x * weight[i];
        }
    }

    // 按空格编号建表，搜索时只搬编号
    for (int i = 0; i < blank_cnt; ++i) {
        int p = blanks[i];
        row_of[i] = p / 9;
        col_of[i] = p % 9;
        box_of[i] = p / 27 * 3 + p % 9 / 3;
        w_of[i] = weight[p];
    }

    best = -1;
    int alive[81];
    for (int i = 0; i < blank_cnt; ++i) alive[i] = i;

    dfs(gain, 0, alive, blank_cnt);

    cout << best << "\n";
    return 0;
}
