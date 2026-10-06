/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 00:19
 * update_at: 2026-10-07 00:19
 */
// 这是 STL 写法：把读入的 N 个数依次放进 vector，再用 sort 排好，最后按空格输出。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n;
vector<ll> a; // 待排序的数列；个数由输入的 N 决定，所以用 vector 而不是定长数组

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll i = 0; i < n; i++) {
        ll x;
        cin >> x;
        a.push_back(x);
    }

    // sort 默认按 < 排序，即从小到大；区间是左闭右开的 [a.begin(), a.end())。
    sort(a.begin(), a.end());

    for (ll i = 0; i < n; i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << a[i];
    }
    cout << '\n';

    return 0;
}
