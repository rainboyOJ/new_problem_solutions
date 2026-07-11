/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 18:04
 * update_at: 2026-07-11 18:05
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
char s[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    long long ans = 0;

    // 枚举所有长度至少为 3 的连续照片。
    for (int l = 1; l <= n; l++) {
        int cnt_g = 0;
        int cnt_h = 0;
        for (int r = l; r <= n; r++) {
            if (s[r] == 'G') {
                cnt_g++;
            } else {
                cnt_h++;
            }

            if (r - l + 1 >= 3 && (cnt_g == 1 || cnt_h == 1)) {
                ans++;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
