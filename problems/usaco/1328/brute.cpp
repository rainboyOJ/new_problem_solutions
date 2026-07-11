/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 21:17
 * update_at: 2026-07-11 21:18
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

string s;
string target = "bessie";

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    int n = (int)s.size();
    long long ans = 0;

    // 枚举所有子串，直接在子串上贪心匹配尽量多的 "bessie"。
    for (int l = 0; l < n; l++) {
        int state = 0;
        int cnt = 0;
        for (int r = l; r < n; r++) {
            if (s[r] == target[state]) {
                state++;
                if (state == 6) {
                    cnt++;
                    state = 0;
                }
            }
            ans += cnt;
        }
    }

    cout << ans << '\n';

    return 0;
}
