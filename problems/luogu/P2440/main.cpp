/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-09 06:46
 * update_at: 2026-08-14 19:34
 */

/* P2440 木材加工 */
/* 二分答案：找最大的切割长度，使切出的段数 >= k。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

int n;
long long k;       // 需要的段数
long long wood[MAXN]; // 每根木材的长度

// 切割长度 mid 时，切出的段数是否 < k（即不可行）。
// check 单调：false false ... false true true ... true。
bool check(long long mid) {
    long long cnt = 0;
    for (int i = 1; i <= n; i++) {
        cnt += wood[i] / mid;
        if (cnt >= k) return false;
    }
    return true;
}

// 在 [l, r] 中查找第一个满足 check(pos) 的位置。
// 要求 check 单调：false false ... false true true ... true。
// 调用时要保证 r 是一个真实或虚拟的可行位置。
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

    cin >> n >> k;
    long long mx = 0;
    for (int i = 1; i <= n; i++) {
        cin >> wood[i];
        if (wood[i] > mx) mx = wood[i];
    }

    // 第一个失败位置；mx+1 是虚拟失败位置（任何木头都切不出 1 段）。
    // 答案 = 失败位置 - 1，即最后一个可行长度；无解时失败位置为 1，答案为 0。
    long long fail_pos = first_true(1, mx + 1);
    cout << fail_pos - 1 << '\n';
    return 0;
}
