/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 14:51
 * update_at: 2026-07-11 14:57
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int T;
int n;
int cnt[MAXN]; // cnt[h] 表示身高 h 的奶牛数量。

void solve_one() {
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cnt[i] = 0;
    }

    for (int i = 1; i <= n; i++) {
        int h;
        cin >> h;
        cnt[h]++;
    }

    int ans = 0;
    bool has_center = false;

    // 从高到低扫。最高出现的身高只能放中间，较低身高需要成对放两边。
    for (int h = n; h >= 1; h--) {
        if (cnt[h] == 0) continue;

        if (!has_center) {
            ans++;
            has_center = true;
        } else if (cnt[h] >= 2) {
            ans += 2;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        solve_one();
    }

    return 0;
}
