/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:14
 * update_at: 2026-10-23 23:14
 */
// brute.cpp：对拍用的独立实现。用「最少插入数 = n - 最长回文子序列长度」，
// 而最长回文子序列 = 原串与反串的最长公共子序列（LCS），O(n^2)，与区间 DP 互相独立。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXL = 1005;

string s;
ll f[MAXL][MAXL]; // f[i][j]：s 前 i 个字符与反串前 j 个字符的 LCS 长度

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    ll n = s.size();
    string r(s.rbegin(), s.rend()); // 反串

    for (ll i = 1; i <= n; ++i) {
        for (ll j = 1; j <= n; ++j) {
            if (s[i - 1] == r[j - 1]) f[i][j] = f[i - 1][j - 1] + 1;
            else f[i][j] = max(f[i - 1][j], f[i][j - 1]);
        }
    }

    // 最长回文子序列以外的字符各需要补一个配对字符
    cout << n - f[n][n] << "\n";
    return 0;
}
