/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:19
 * update_at: 2026-10-05 07:19
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 1005;          // 题目给定 n <= 1000
int h[MAXN];                    // 导弹高度序列
int rev[MAXN];                  // 翻转后的高度序列
int n;                          // 实际导弹个数
int tails[MAXN];                // tails[i] = 长度为 i+1 的子序列末尾元素的最小值
int tails_len;                  // tails 数组的有效元素个数

// 二分查找：找 tails 中第一个 >= x 的位置（不降版本用）
// 范围 [0, tails_len)
int bisect_left_tails(int x) {
    int lo = 0, hi = tails_len; // 答案落在 [lo, hi)
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (tails[mid] < x) {
            lo = mid + 1;       // 还在左边，答案靠右
        } else {
            hi = mid;           // tails[mid] >= x，可以是答案
        }
    }
    return lo;
}

// 二分查找：找 tails 中第一个 > x 的位置（严格上升版本用）
int bisect_right_tails(int x) {
    int lo = 0, hi = tails_len;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (tails[mid] <= x) {
            lo = mid + 1;       // 还在左边或相等，答案靠右
        } else {
            hi = mid;           // tails[mid] > x，可以是答案
        }
    }
    return lo;
}

// 计算序列 a[0..len-1] 的最长子序列长度。
// strict = true  -> 严格上升，用 bisect_right
// strict = false -> 不下降，用 bisect_left
int lis_length(int* a, int len, bool strict) {
    tails_len = 0;
    for (int i = 0; i < len; ++i) {
        int pos;
        if (strict) {
            pos = bisect_right_tails(a[i]);
        } else {
            pos = bisect_left_tails(a[i]);
        }
        if (pos == tails_len) {
            tails[pos] = a[i];   // 接成更长的子序列
            ++tails_len;
        } else {
            tails[pos] = a[i];   // 把该长度的最小末尾压低
        }
    }
    return tails_len;
}

int main() {
    // 读入：导弹高度序列（空格分隔，直到 EOF）
    n = 0;
    int x;
    while (scanf("%d", &x) == 1) {
        h[n++] = x;
        rev[n - 1] = x;         // 同步存进翻转数组，后面再倒置
    }

    // 构造翻转序列：把 rev 倒过来变成正序
    for (int i = 0; i < n; ++i) {
        rev[i] = h[n - 1 - i];
    }

    // 第一问：最长不升子序列 = 翻转序列的最长不下降子序列
    int best_one = lis_length(rev, n, false);

    // 第二问：Dilworth 定理 -> 最少系统数 = 原序列的最长严格上升子序列
    int best_split = lis_length(h, n, true);

    printf("%d\n%d\n", best_one, best_split);
    return 0;
}