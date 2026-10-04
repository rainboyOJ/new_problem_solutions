/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:13
 * update_at: 2026-10-04 23:13
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n; // 输入的正整数 n

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    // 奇偶性只看二进制最低位：n & 1 == 1 是奇数，否则是偶数
    if (n & 1) cout << "odd\n";
    else cout << "even\n";

    return 0;
}