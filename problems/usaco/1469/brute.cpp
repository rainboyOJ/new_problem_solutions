/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:26
 * update_at: 2026-07-11 15:29
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
int a[MAXN], b[MAXN];
long long ans[MAXN]; // ans[c] 表示恰好 c 头奶牛能体检的反转方案数。

int count_match_after_reverse(int l, int r) {
    int cnt = 0;

    for (int i = 1; i <= n; i++) {
        int value = a[i];
        if (l <= i && i <= r) {
            value = a[l + r - i];
        }

        if (value == b[i]) cnt++;
    }

    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    // 小数据暴力：直接枚举所有反转区间，再完整计算体检数量。
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            int cnt = count_match_after_reverse(l, r);
            ans[cnt]++;
        }
    }

    for (int c = 0; c <= n; c++) {
        cout << ans[c] << '\n';
    }

    return 0;
}
