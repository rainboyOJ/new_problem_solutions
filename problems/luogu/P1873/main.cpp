/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-09 06:46
 * update_at: 2026-08-14 19:14
 */

/* P1873 [COCI 2011/2012 #5] EKO / 砍树 */
/* 二分答案：找最大切割高度，使获得的木材总量 >= need。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int n;
long long need;    // 需要的木材量
long long h[MAXN]; // 每棵树的高度

// 切割高度 mid 时获得的木材是否 >= need。
// check 单调：true true ... true false false ... false。
bool check(long long mid) {
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        if (h[i] > mid) {
            sum += h[i] - mid;
            if (sum >= need) return true;
        }
    }
    return sum >= need;
}

// 在 [l, r] 中查找最后一个满足 check(pos) 的位置。
// 要求 check 单调：true true ... true false false ... false。
// 调用时要保证 l 是一个真实或虚拟的可行位置。
long long last_true(long long l, long long r) {
    while (l < r) {
        long long mid = l + (r - l + 1) / 2;
        if (check(mid)) l = mid;
        else r = mid - 1;
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

    // 高度 0 一定可行（获得全部木材），虚拟可行位置作为左端点
    cout << last_true(0, max_h) << '\n';
    return 0;
}
