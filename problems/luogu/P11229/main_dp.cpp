/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * date: 2026-07-07 00:00:00
 */
// main_dp.cpp：DP 预处理每个木棍数的最优(位数,首数字)，O(N*10) 预处理 + O(1) 查询。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int stick[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

// best_len_0[i] / best_digit_0[i]：i 根木棍的最优方案（允许首数字为 0，用于非首位）
int best_len_0[MAXN], best_digit_0[MAXN];
// best_len_1[i] / best_digit_1[i]：i 根木棍的最优方案（不允许首数字为 0，用于第一位）
int best_len_1[MAXN], best_digit_1[MAXN];

// 比较 (len_a, digit_a) 是否优于 (len_b, digit_b)
// 更优：位数更少，或位数相同且首数字更小
bool better(int len_a, int digit_a, int len_b, int digit_b) {
    if (len_a == 0) return false; // 当前状态无效
    if (len_b == 0) return true;  // 被比较状态无效
    if (len_a != len_b) return len_a < len_b;
    return digit_a < digit_b;
}

void precompute() {
    for (int i = 2; i < MAXN; i++) {
        // 填 best_0：首数字允许为 0
        for (int d = 0; d <= 9; d++) {
            int cost = stick[d];
            if (i < cost) continue;
            int rest = i - cost;
            if (rest == 1) continue; // 剩余 1 根无法拼出任何数字
            int cand_len = (rest == 0) ? 1 : best_len_0[rest] + 1;
            int cand_digit = d;
            if (better(cand_len, cand_digit, best_len_0[i], best_digit_0[i])) {
                best_len_0[i] = cand_len;
                best_digit_0[i] = cand_digit;
            }
        }

        // 填 best_1：首数字不允许为 0
        for (int d = 1; d <= 9; d++) {
            int cost = stick[d];
            if (i < cost) continue;
            int rest = i - cost;
            if (rest == 1) continue;
            int cand_len = (rest == 0) ? 1 : best_len_0[rest] + 1;
            int cand_digit = d;
            if (better(cand_len, cand_digit, best_len_1[i], best_digit_1[i])) {
                best_len_1[i] = cand_len;
                best_digit_1[i] = cand_digit;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        if (n == 1 || best_len_1[n] == 0) {
            cout << -1 << '\n';
            continue;
        }
        // 输出第一位（由 best_1 确定），剩余用 best_0 递推
        int cur = n;
        cout << best_digit_1[cur];
        cur -= stick[best_digit_1[cur]];
        while (cur > 0) {
            cout << best_digit_0[cur];
            cur -= stick[best_digit_0[cur]];
        }
        cout << '\n';
    }

    return 0;
}
