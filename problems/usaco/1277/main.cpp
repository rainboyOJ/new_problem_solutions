/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:10
 * update_at: 2026-07-11 17:11
 */
#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;

int solve(string s) {
    int n = (int)s.size();
    if (n < 3) {
        return -1;
    }

    int ans = INF;

    // 枚举最终保留下来的长度为 3 的子串的中间位置。
    for (int i = 1; i <= n - 2; i++) {
        if (s[i] != 'O') {
            continue;
        }

        int cur = n - 3; // 删除左右多余字符
        if (s[i - 1] != 'M') {
            cur++;
        }
        if (s[i + 1] != 'O') {
            cur++;
        }

        if (cur < ans) {
            ans = cur;
        }
    }

    if (ans == INF) {
        return -1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;
        cout << solve(s) << '\n';
    }

    return 0;
}
