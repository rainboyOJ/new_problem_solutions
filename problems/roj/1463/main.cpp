/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:12
 * update_at: 2026-10-06 00:12
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll LIMIT = 2000000; // 题目规定：答案超过 2×10^6 就输出 -1，所以最多模拟这么多项

ll A, B, C;

void solve() {
    // 数列是函数迭代，重复一定会出现；逐项模拟，第一次撞上旧值即答案。
    // 每项都在 [0, C) 内，但 C 可达 10^9 开不下标记数组；而模拟步数不超过 2×10^6，
    // 所以用哈希集合只登记真正出现过的值，集合大小与值域无关。
    unordered_set<ll> seen; // seen 记录已经出现过的项
    seen.reserve(LIMIT + 1);

    ll value = 1; // a_0 = 1，它也可能再次出现，必须先放进集合
    seen.insert(value);

    for (ll i = 1; i <= LIMIT; i++) {
        value = (A * value + value % B) % C;
        if (seen.count(value) != 0) {
            cout << i << '\n'; // value 之前出现过，标号 i 就是第一次出现重复的位置
            return;
        }
        seen.insert(value);
    }

    cout << -1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> A >> B >> C;
    solve();

    return 0;
}
