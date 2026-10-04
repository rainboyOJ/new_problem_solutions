/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 11:29
 * update_at: 2026-10-03 11:29
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// A 题枚举每个日期串的所有可能匹配位置组合；B 题扫描全部 c0 取值取最近的一个。
// 两道小问的规模都是固定的，暴力只用来独立验证正解的贪心/单调性结论。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

// 试题 A 给定的 100 个数字。
int a[MAXN];

// 当前正在匹配的 8 位日期串。
string target_date;

// 递归的层数：正在决定日期串第几位的落点。
// 返回是否找到一组下标，使日期串成为 a[] 的子序列。
// brute 不使用“最靠左落点最优”的贪心结论，而是把所有下标组合都试一遍。
bool dfs_A(int digit, int start) {
    if (digit == 8) {
        return true;
    }
    int want = target_date[digit] - '0';
    for (int i = start; i < 100; i++) {
        if (a[i] == want) {
            if (dfs_A(digit + 1, i + 1)) {
                return true;
            }
        }
    }
    return false;
}

// 每个月的天数，2023 不是闰年。
int month_day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

// 试题 A：枚举 2023 年的每一天，用 dfs_A 判断这一天能否被拼出来。
int solve_A() {
    int ans = 0;
    for (int m = 1; m <= 12; m++) {
        for (int d = 1; d <= month_day[m]; d++) {
            char buf[16];
            snprintf(buf, sizeof(buf), "2023%02d%02d", m, d);
            target_date = buf;
            if (dfs_A(0, 0)) {
                ans++;
            }
        }
    }
    return ans;
}

// 试题 B：暴力枚举 0 的个数 c0，直接用熵公式算出 H(c0)，
// 记录与题目给定熵值差距最小的那个 c0。
// 不利用 H(c0) 的单调性，也不提前退出，遍历全部 n/2 + 1 个取值。
int solve_B() {
    const int n = 23333333;
    const double target = 11625907.5798;
    double best_diff = 1e18;
    int best_c0 = -1;
    for (int c0 = 0; c0 <= n / 2; c0++) {
        int c1 = n - c0;
        double p0 = (double)c0 / n;
        double p1 = (double)c1 / n;
        double h = 0.0;
        // c0 或 c1 为 0 时该项占比为 0，熵的贡献记 0，不对 log2(0) 求值。
        if (c0 > 0) {
            h -= (double)c0 * p0 * log2(p0);
        }
        if (c1 > 0) {
            h -= (double)c1 * p1 * log2(p1);
        }
        double diff = fabs(h - target);
        if (diff < best_diff) {
            best_diff = diff;
            best_c0 = c0;
        }
    }
    return best_c0;
}

int main() {
    int given[100] = {
        5, 6, 8, 6, 9, 1, 6, 1, 2, 4, 9, 1, 9, 8, 2, 3, 6, 4, 7, 7,
        5, 9, 5, 0, 3, 8, 7, 5, 8, 1, 5, 8, 6, 1, 8, 3, 0, 3, 7, 9,
        2, 7, 0, 5, 8, 8, 5, 7, 0, 9, 9, 1, 9, 4, 4, 6, 8, 6, 3, 3,
        8, 5, 1, 6, 3, 4, 6, 7, 0, 7, 8, 2, 7, 6, 8, 9, 5, 6, 5, 6,
        1, 4, 0, 1, 0, 0, 9, 4, 8, 0, 9, 1, 2, 8, 5, 0, 2, 5, 3, 3,
    };
    for (int i = 0; i < 100; i++) {
        a[i] = given[i];
    }

    char type;
    if (!(cin >> type)) {
        return 0;
    }
    if (type == 'A') {
        printf("%d\n", solve_A());
    } else if (type == 'B') {
        printf("%d\n", solve_B());
    }
    return 0;
}
