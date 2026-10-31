/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 18:55
 * update_at: 2026-10-31 18:58
 */
// brute.cpp：直接把字符串展开，再一组一组数对称位置上字符不同的组数。
// 只有字符串总长很小的时候才能用，专门用来和 main.cpp 对拍。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string s;
    for (int i = 0; i < n; ++i) {
        ll len;
        char ch;
        cin >> len >> ch;
        for (ll k = 0; k < len; ++k) s.push_back(ch);
    }

    int L = (int)s.size();
    ll ans = 0;
    for (int i = 0; i < L / 2; ++i) {
        if (s[i] != s[L - 1 - i]) ++ans;
    }
    cout << ans << '\n';
    return 0;
}
