/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 00:19
 * update_at: 2026-10-07 00:19
 */
// 这是 STL 写法：用 vector<ll> 存下所有学校的预计分数线，sort 排好序后，
// 对每个学生分数用 lower_bound 定位第一个不小于它的分数线，再和它的前一个位置比较取较小差值。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll m, n;      // m 所学校，n 位学生
vector<ll> a; // 排序后的学校预计分数线

// 返回分数线中与估分 x 相差最小的那个差值。
// lower_bound 返回第一个不小于 x 的位置 it，分三种情况：
//   it == a.end()   ：所有分数线都小于 x，离它最近的是最后一个元素；
//   it == a.begin() ：所有分数线都不小于 x，离它最近的是第一个元素；
//   其余情况：最近分数线一定落在 *it 和 *(it - 1) 这两个候选里，取较小差值。
ll min_gap(ll x) {
    auto it = lower_bound(a.begin(), a.end(), x);

    if (it == a.end()) {
        return x - *(it - 1);
    }
    if (it == a.begin()) {
        return *it - x;
    }

    ll upper_gap = *it - x;       // 右侧候选：第一个不小于 x 的分数线
    ll lower_gap = x - *(it - 1); // 左侧候选：它前面的那条分数线
    return min(upper_gap, lower_gap);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;

    a.resize(m);
    for (ll i = 0; i < m; i++) {
        cin >> a[i];
    }

    // 二分查找的前提是数据有序：先把分数线升序排好
    sort(a.begin(), a.end());

    ll ans = 0; // 不满意度之和最多约 1e5 * 1e6 = 1e11，累加变量必须用 ll
    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        ans += min_gap(x);
    }

    cout << ans << '\n';

    return 0;
}
