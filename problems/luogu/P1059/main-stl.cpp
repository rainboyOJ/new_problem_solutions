/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 23:38
 * update_at: 2026-10-06 23:55
 */
// 这是 STL 写法：用 vector 存下所有随机数，靠 sort + unique + erase 三行完成去重与排序。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n;
vector<int> a; // 随机数序列；值域只有 1..1000，元素用 int 足够

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    // 书上三行组合：sort 让相等的值相邻，unique 合并相邻重复并返回新的逻辑末尾，
    // erase 把逻辑末尾之后的尾段真正删掉，容器 size 才变小。
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());

    ll m = a.size(); // 去重后的个数
    cout << m << '\n';
    for (ll i = 0; i < m; i++) {
        if (i) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';

    return 0;
}
