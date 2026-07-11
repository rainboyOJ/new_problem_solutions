/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:02
 * update_at: 2026-07-11 15:06
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, q;
string s;

bool is_moo(int i, int j, int k) {
    return s[i] != s[j] && s[j] == s[k];
}

long long calc_value(int i, int j, int k) {
    return 1LL * (j - i) * (k - j);
}

long long brute_query(int l, int r) {
    long long ans = -1;

    // 小数据暴力：直接枚举所有 i < j < k。
    for (int i = l; i <= r; i++) {
        for (int j = i + 1; j <= r; j++) {
            for (int k = j + 1; k <= r; k++) {
                if (is_moo(i, j, k)) {
                    long long value = calc_value(i, j, k);
                    if (ans < value) ans = value;
                }
            }
        }
    }

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    cin >> s;
    s = " " + s;

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << brute_query(l, r) << '\n';
    }

    return 0;
}
