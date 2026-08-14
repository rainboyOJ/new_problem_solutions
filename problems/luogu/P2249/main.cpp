/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-08-14 19:07
 */

/* P2249 【深基13.例1】查找 */
/* 在单调不减数组中二分查找目标第一次出现的位置（从 1 开始编号）。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
const int MAXM = 100005;

int n, m;
int a[MAXN]; // 单调不减数组
int x;       // 当前要查找的目标值

// check 单调：false false ... false true true ... true
// a[pos] >= x 从某处开始恒为 true
bool check(int pos) {
    return a[pos] >= x;
}

// 在 [l, r] 中查找第一个满足 check(pos) 的位置。
// 要求 r 是一个真实或虚拟的可行位置。
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

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 哨兵位置 n+1：表示不存在 >= x 的元素。
    a[n + 1] = INT_MAX;

    for (int i = 1; i <= m; i++) {
        cin >> x;

        // 第一个 a[pos] >= x 的位置，若等于 x 说明 x 存在
        int pos = first_true(1, n + 1);
        if (pos <= n && a[pos] == x) {
            cout << pos;
        } else {
            cout << -1;
        }
        if (i == m) {
            cout << '\n';
        } else {
            cout << ' ';
        }
    }

    return 0;
}
