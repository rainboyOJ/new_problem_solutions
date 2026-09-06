/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-06 19:06
 * update_at: 2026-09-06 19:22
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n;
    cin >> n;

    // 先判断平方复杂度，再判断线性复杂度，常数复杂度总能通过。
    if (n <= 500000000LL / n) {
        cout << "O(n^2)\n";
    } else if (n <= 500000000LL) {
        cout << "O(n)\n";
    } else {
        cout << "O(1)\n";
    }
    return 0;
}
