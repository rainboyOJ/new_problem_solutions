/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 01:16
 * update_at: 2026-10-07 01:16
 */
// 这是 STL 写法：用 set<ll> 的 count / insert 边读边判断“这个数之前出现过吗”。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;

typedef long long ll;

ll n;
ll a[MAXN];      // 当前一组输入的数字，按读入顺序保存
set<ll> seen;    // 已经输出过的数字，只用来判重，不遍历它输出

// 处理一组数据：第一次出现的数字按读入顺序输出，重复的丢掉。
void solve_one() {
    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }

    seen.clear(); // 多组数据，每组开始都要清空集合

    bool first = true;
    for (ll i = 1; i <= n; i++) {
        // count 只查询元素在不在集合里，不会往集合里添加数据
        if (seen.count(a[i]) > 0) {
            continue;
        }
        seen.insert(a[i]); // 第一次出现的数记进集合，重复插入不会改变集合

        if (!first) {
            cout << ' ';
        }
        cout << a[i];
        first = false;
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll T;
    cin >> T;
    while (T--) {
        solve_one();
    }

    return 0;
}
