/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:09
 * update_at: 2026-07-11 15:11
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n;
int cnt[MAXN]; // cnt[x] 表示数值 x 在原数组中出现了多少次。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    int missing_lt_i = 0; // 0..i-1 中缺失的数的个数。

    for (int i = 0; i <= n; i++) {
        cout << max(cnt[i], missing_lt_i) << '\n';

        if (cnt[i] == 0) {
            missing_lt_i++;
        }
    }

    return 0;
}
