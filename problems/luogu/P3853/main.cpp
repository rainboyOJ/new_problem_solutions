/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-08-14 19:14
 */

/* P3853 [TJOI2007] 路标设置 */
/* 二分答案：找最小的最大间距，使需要新增的路标数 <= limit。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int length, n, limit; // 道路长度、已有路标数、最多可新增数
int pos[MAXN];        // 已有路标位置
int gap[MAXN];        // 相邻路标间距

// 最大间距 mid 是否可行：需要新增的路标数不超过 limit。
// check 单调：false false ... false true true ... true。
bool check(int mid) {
    int need = 0;
    for (int i = 1; i < n; i++) {
        // 长度为 gap[i] 的线段，间距不超过 mid 需要插入的路标数
        need += (gap[i] - 1) / mid;
    }
    return need <= limit;
}

// 在 [l, r] 中查找第一个满足 check(pos) 的位置。
// 要求 check 单调：false false ... false true true ... true。
// 调用时要保证 r 是一个真实或虚拟的可行位置。
int first_true(int l, int r) {
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> length >> n >> limit;
    for (int i = 1; i <= n; i++) {
        cin >> pos[i];
    }

    // 预处理相邻间距
    int max_gap = 0;
    for (int i = 2; i <= n; i++) {
        gap[i - 1] = pos[i] - pos[i - 1];
        if (gap[i - 1] > max_gap) max_gap = gap[i - 1];
    }

    // max_gap 一定可行（不需要新增路标），作为虚拟可行位置
    cout << first_true(1, max_gap) << '\n';
    return 0;
}
