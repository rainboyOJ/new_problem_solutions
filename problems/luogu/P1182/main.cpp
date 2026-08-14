/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-09 06:46
 * update_at: 2026-08-14 19:14
 */

/* P1182 数列分段 Section II */
/* 二分答案：找最小的最大段和，使分段数不超过 m。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, m;
long long a[MAXN]; // 数列

// 最大段和 mid 是否可行：最少分段数不超过 m。
// check 单调：false false ... false true true ... true。
bool check(long long mid) {
    int segments = 1;
    long long cur_sum = 0;

    for (int i = 1; i <= n; i++) {
        if (cur_sum + a[i] <= mid) {
            cur_sum += a[i];
        } else {
            segments++;
            cur_sum = a[i];
        }
    }

    return segments <= m;
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

    cin >> n >> m;
    long long max_a = 0, sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] > max_a) max_a = a[i];
        sum += a[i];
    }

    // 总和一定可行（只分 1 段），作为虚拟可行位置
    cout << first_true(max_a, sum) << '\n';
    return 0;
}
