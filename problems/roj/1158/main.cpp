/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:50
 * update_at: 2026-10-05 03:50
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n;

// 递归求 1+2+...+n：边界 n==0 返回 0；否则本层认领 n，把 n-1 交给下一层。
ll sum_to(ll n) {
    if (n == 0) return 0;
    return n + sum_to(n - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cout << sum_to(n) << '\n';

    return 0;
}
