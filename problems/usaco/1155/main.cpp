/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 18:04
 * update_at: 2026-07-11 18:05
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 500005;

int n;
char s[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i];
    }

    ll ans = 0;

    for (int i = 1; i <= n; i++) {
        ll left_cnt = 0;
        ll right_cnt = 0;

        // 向左数连续的异色牛。
        int p = i - 1;
        while (p >= 1 && s[p] != s[i]) {
            left_cnt++;
            p--;
        }

        // 向右数连续的异色牛。
        p = i + 1;
        while (p <= n && s[p] != s[i]) {
            right_cnt++;
            p++;
        }

        // 当前牛作为唯一的少数派：左右各取一段，或者只在一侧取至少两头异色牛。
        ans += left_cnt * right_cnt;
        if (left_cnt >= 2) {
            ans += left_cnt - 1;
        }
        if (right_cnt >= 2) {
            ans += right_cnt - 1;
        }
    }

    cout << ans << '\n';

    return 0;
}
