/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:14
 * update_at: 2026-10-23 23:14
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXL = 1005;

string s;
ll f[MAXL][MAXL]; // f[i][j]：把 s[i..j] 变成回文串最少需要的插入字符数（i、j 为 1 开始的下标）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    ll n = s.size();
    // 下标整体右移一位，方便按题意从 1 开始
    string t = " " + s;

    // 长度为 1 的区间本身是回文，插入数为 0
    for (ll i = 1; i <= n; ++i) f[i][i] = 0;

    // len 是区间长度，从 2 开始，从小区间推出大区间
    for (ll len = 2; len <= n; ++len) {
        for (ll i = 1; i + len - 1 <= n; ++i) {
            ll j = i + len - 1;
            if (t[i] == t[j]) {
                // 两端已经配对，成本等于去掉两端后的子区间
                f[i][j] = f[i + 1][j - 1];
            } else {
                // 两端不配对：在左边补一个 t[j]，或在右边补一个 t[i]，取较小者
                f[i][j] = min(f[i + 1][j], f[i][j - 1]) + 1;
            }
        }
    }

    cout << f[1][n] << "\n";
    return 0;
}
