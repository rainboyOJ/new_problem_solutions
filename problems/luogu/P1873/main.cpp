/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-09 06:46
 * update_at: 2026-10-27 20:50
 */

/* P1873 [COCI 2011/2012 #5] EKO / 砍树 */
/* 二分答案：找最大切割高度，使获得的木材总量 >= need。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int n;
long long need;    // 需要的木材量
long long h[MAXN]; // 每棵树的高度

// 切割高度 mid 时得到的木材是否不足 need（即失败）。
// check 单调：false false ... false true true ... true。
bool check(long long mid) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        if (h[i] > mid) {
            sum += h[i] - mid;
            if (sum >= need) return false;
        }
    }
    return true;
}

// 在 [l, r] 中查找第一个满足 check(pos) 的位置，即第一个失败位置。
// 要求 check 单调：false false ... false true true ... true。
// 调用时要保证 r 是一个真实或虚拟的失败位置。
long long first_true(long long l, long long r) {
    while (l < r) {
        long long mid = l + (r - l) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    return l;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> need;
    long long max_h = 0;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        if (h[i] > max_h) max_h = h[i];
    }

    // 第一个失败位置；max_h + 1 是虚拟失败位置（锯片高过所有树，木材为 0）。
    // 答案 = 失败位置 - 1，即最后一个可行高度。
    long long fail_pos = first_true(0, max_h + 1);
    cout << fail_pos - 1 << '\n';
    return 0;
}
