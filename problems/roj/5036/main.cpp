/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 22:46
 * update_at: 2026-10-08 22:46
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> a; // a[0..n-1] 按输入顺序保存读到的 n 个数（题面：整数不超过 100 个）

// 按题面要求逆序打印：元素之间用单个空格隔开，行末不留多余空格。
void solve() {
    ll x;
    // 题面只给「一行 n 个数」、不单独给 n，所以只能一直读到文件末尾（EOF）为止 —— 本题考点。
    while (cin >> x) {
        a.push_back(x);
    }

    ll n = a.size();
    for (ll i = n - 1; i >= 0; i--) {
        if (i != n - 1) {
            cout << " ";
        }
        cout << a[i];
    }
    if (n > 0) {
        cout << "\n"; // 非空输入时行末换行；空输入则零输出
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
