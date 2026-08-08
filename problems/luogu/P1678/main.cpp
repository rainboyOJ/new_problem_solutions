/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-02 01:36
 * update_at: 2026-08-02 01:36
 */

/* P1678 烦恼的高考志愿 */
/* 排序分数线后，对每个学生分数用 first_true 找第一个 >= score 的位置，再比较前后两个候选。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXM = 100000 + 5;

int m, n;          // m 所学校，n 位学生
int score;         // 当前学生估分
int a[MAXM + 2];   // 分数线，a[0] 为 -INF 哨兵，a[m+1] 为 +INF 哨兵

// 检查 a[pos] 是否不小于当前学生估分。
bool check(int pos) {
    return a[pos] >= score;
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

    cin >> m >> n;
    for (int i = 1; i <= m; ++i) cin >> a[i];

    sort(a + 1, a + m + 1);

    // 两个哨兵：保证二分查找永远不会越界。
    a[0] = INT_MIN;      // 虚拟位置 0：表示不存在 <= score 的元素
    a[m + 1] = INT_MAX;  // 虚拟位置 m+1：表示不存在 >= score 的元素

    long long ans = 0;
    while (n--) {
        cin >> score;

        // 第一个 >= score 的分数线位置，一定存在（最坏是 m+1 哨兵）
        int pos = first_true(1, m + 1);

        // 最近分数线只在 pos 和 pos-1 两个候选中，取差值的较小者
        ans += min<long long>((long long)a[pos] - score, (long long)score - a[pos - 1]);
    }

    cout << ans << '\n';
    return 0;
}
