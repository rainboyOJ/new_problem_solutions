/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 11:29
 * update_at: 2026-10-03 11:29
 */
// main.cpp：P9239 填空问题正解。
// 两道小问的输入都只是题面写死的常量（A 题的 100 个数字、B 题的 n 和熵值），
// 所以这里把“答案是怎么算出来的”完整写出来，而不是直接 printf 两个数字。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

// 试题 A 给定的 100 个数字，每个都在 0..9 之间。
int a[MAXN];

// pos[L] = 贪心匹配日期串前 L 位后，第 L 位落在 a[] 中的最小下标。
// pos[0] 用 -1 表示“还没有匹配任何字符”。
int pos[10];

// 每个月的天数，2023 不是闰年，2 月按 28 天算。
int month_day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const int LEN_B = 23333333;              // 试题 B 的 01 串长度 n
const double ENTROPY_B = 11625907.5798;  // 试题 B 给定的信息熵

// 判断 8 位日期串 d 能否作为 a[] 的子序列出现。
// 思路：第 L 位取在 pos[L-1] 之后最靠左的位置，不会让后面的匹配变难。
bool can_form(const string & d) {
    for (int L = 0; L <= 8; L++) {
        pos[L] = 1000000;
    }
    pos[0] = -1;
    for (int L = 1; L <= 8; L++) {
        int want = d[L - 1] - '0';
        // 从上一个落点的右边开始，找第一个等于 want 的数字。
        for (int i = pos[L - 1] + 1; i < 100; i++) {
            if (a[i] == want) {
                pos[L] = i;
                break;
            }
        }
        if (pos[L] == 1000000) {
            return false;
        }
    }
    return true;
}

// 试题 A：枚举 2023 年的 365 个日期，逐个判断是不是 a[] 的子序列。
// 直接枚举日期本身，同一个日期天然只被统计一次。
int solve_a() {
    int ans = 0;
    for (int m = 1; m <= 12; m++) {
        for (int d = 1; d <= month_day[m]; d++) {
            char buf[16];
            snprintf(buf, sizeof(buf), "2023%02d%02d", m, d);
            string date = buf;
            if (can_form(date)) {
                ans++;
            }
        }
    }
    return ans;
}

// 计算 0 出现 c0 次、1 出现 c1 = n - c0 次时的信息熵：
// H = -c0 * p0 * log2(p0) - c1 * p1 * log2(p1)，其中 p0 = c0/n，p1 = c1/n。
// 某一类出现 0 次时规定它贡献 0（不取 log2(0)）。
double entropy_of(int c0, int n) {
    int c1 = n - c0;
    double p0 = (double)c0 / n;
    double p1 = (double)c1 / n;
    double h = 0.0;
    if (c0 > 0) {
        h -= (double)c0 * p0 * log2(p0);
    }
    if (c1 > 0) {
        h -= (double)c1 * p1 * log2(p1);
    }
    return h;
}

// 试题 B：H(c0) 关于 c0 在 [0, n/2] 上单调递增（峰值在 c0 = n/2），
// 所以“离目标熵最近”的 c0 一定在 H 穿过目标值的那个位置附近。
// 先二分出最大的、满足 H(c0) <= 目标值的 c0，再和它的右邻居比一比距离即可。
int solve_b() {
    int n = LEN_B;
    double target = ENTROPY_B;

    // 二分：H(0) = 0 <= target，且 H(n/2) 远大于 target，区间内一定有解。
    int left = 0, right = n / 2;
    int below = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (entropy_of(mid, n) <= target) {
            below = mid;   // mid 还在目标值下方，可能还能更大
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    int best = below;
    int next = below + 1;
    if (next <= n / 2) {
        double diff_best = fabs(entropy_of(best, n) - target);
        double diff_next = fabs(entropy_of(next, n) - target);
        if (diff_next < diff_best) {
            best = next;
        }
    }
    return best;
}

int main() {
    char type;
    if (!(cin >> type)) {
        return 0;
    }

    // 题面写死的 100 个数字。
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

    if (type == 'A') {
        printf("%d\n", solve_a());
    } else if (type == 'B') {
        printf("%d\n", solve_b());
    }
    return 0;
}
