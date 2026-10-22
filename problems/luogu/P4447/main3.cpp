/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-22 23:45
 * update_at: 2026-10-22 23:45
 */
// main3.cpp：第三层解法，扫描连续段，O(n log n)。
// 本层针对 5~6 号测试点：n <= 1e5，但 a_i 互不相同。
//
// 关键观察：既然没有两个队员实力值相同，就不会有两个人争抢同一条链的位置。
// 于是把 a[] 排序后，它自动被切成若干段「连续区间」，区间之间差至少 2。
//
// 为什么每段连续区间整体就是一组？
//   - 段内数值连续且互不相同，天然满足「连续」和「不重复」，可以直接作为一组；
//   - 若把它切成更小的组，只可能让最小的组更小，不会让答案变大。
// 所以最优方案就是「每段连续区间各成一组」，答案取这些段里最短的那一段。
//
// 注意是取「最短」而不是「最长」：题目要最大化最小组人数，而最短的连续段
// 已经决定了上限，段内再细切只会更差。例如 [1,2,10,11,12] 分成 2 组，
// 最短段长 2，答案就是 2，而不是最长段的 3。
//
// 与第四层的关系：本层其实是第四层在无重复情形下的退化 —— 每个值的桶里
// 最多只有一个元素，堆退化成普通栈，于是不需要堆，扫一遍连续段即可。
// 值一旦允许重复（7~8 号点），就必须用桶 + 堆，见 main4.cpp。
//
// ⚠ 本层直接用「整段作为一组」，一旦存在重复值就会给出错误答案
// （例如 {-1,0,0,1,1,2,3} 正确是 3，本层会算成 2）。所以读入后先检查
// 是否有重复，有则提示改用 main4.cpp，避免静默返回错解。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
int a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    sort(a + 1, a + n + 1);

    // 本层的前提是「实力值互不相同」，检查一遍，不满足就明确提示
    for (int i = 2; i <= n; i++) {
        if (a[i] == a[i - 1]) {
            cerr << "[main3] 本层只适用于 a_i 互不相同的 5~6 号测试点，"
                 << "但读到了重复的实力值 " << a[i]
                 << "；请改用 main4.cpp（桶 + 堆）\n";
            return 1;
        }
    }

    // 扫描排序后的数组，找每一段满足 a[j+1] == a[j] + 1 的连续区间
    int answer = n;  // 最小组人数，先取最坏上界
    int left = 1;
    while (left <= n) {
        int right = left;
        while (right + 1 <= n && a[right + 1] == a[right] + 1) {
            right++;
        }
        // 区间 [left, right] 就是一组，人数是 right - left + 1
        answer = min(answer, right - left + 1);
        left = right + 1;
    }

    cout << answer << '\n';
    return 0;
}
