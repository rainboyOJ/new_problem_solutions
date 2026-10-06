/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 00:18
 * update_at: 2026-10-07 00:27
 */
/* P2249 【深基13.例1】查找 */
/* STL 写法：用 vector<ll> 保存单调不减数组，用 lower_bound 找第一个不小于 x 的位置。 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n, m;
vector<ll> numbers; // 单调不减的待查询数组，numbers[0] 是第 1 个数

void read_input() {
    cin >> n >> m;
    numbers.resize(n);
    for (ll i = 0; i < n; i++) {
        cin >> numbers[i];
    }
}

// 依次回答 m 个询问，答案用空格隔开输出在同一行。
void solve() {
    for (ll i = 1; i <= m; i++) {
        ll x;
        cin >> x;

        // lower_bound 返回第一个“不小于 x”的位置（迭代器）。
        auto it = lower_bound(numbers.begin(), numbers.end(), x);

        if (it == numbers.end() || *it != x) {
            // 下界跑到末尾，或下界处的值并不等于 x，说明 x 不存在。
            cout << -1;
        } else {
            // it - numbers.begin() 是 0 开始的下标，题目要的是 1 开始的编号。
            cout << it - numbers.begin() + 1;
        }

        if (i == m) {
            cout << '\n';
        } else {
            cout << ' ';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
