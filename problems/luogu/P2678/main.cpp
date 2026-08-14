/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-09 06:46
 * update_at: 2026-08-14 19:32
 */

/* P2678 [NOIP 2015 提高组] 跳石头 */
/* 二分答案：找最大的最小跳跃距离，使移除石头数不超过 M。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50000 + 5;

long long L;        // 起点到终点的距离
int N, M;           // 石头数，最多移除数
long long stone[MAXN]; // 石头位置，stone[N+1] = L 终点

// 最小跳跃距离 mid 是否不可行：需要移除的石头数超过 M。
// check 单调：false false ... false true true ... true。
bool check(long long mid) {
    long long removed = 0;
    long long last = 0;

    for (int i = 1; i <= N + 1; i++) {
        if (stone[i] - last < mid) {
            removed++;
        } else {
            last = stone[i];
        }
        if (removed > M) return true;
    }

    return false;
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

    cin >> L >> N >> M;
    for (int i = 1; i <= N; i++) cin >> stone[i];
    sort(stone + 1, stone + N + 1);
    stone[N + 1] = L;

    // 第一个失败位置；L+1 是虚拟失败位置（距离 L+1 必须移除全部石头）。
    // 答案 = 失败位置 - 1，即最后一个可行距离。
    long long fail_pos = first_true(0, L + 1);
    cout << fail_pos - 1 << '\n';
    return 0;
}
