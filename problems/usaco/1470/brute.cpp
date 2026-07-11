/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 18:26
 * update_at: 2026-07-11 18:30
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 15;

int n;
int a[MAXN], b[MAXN], cur[MAXN];

int count_checked_after_reverse(int l, int r) {
    for (int i = 1; i <= n; i++) {
        cur[i] = a[i];
    }

    int x = l;
    int y = r;
    while (x < y) {
        swap(cur[x], cur[y]);
        x++;
        y--;
    }

    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (cur[i] == b[i]) {
            cnt++;
        }
    }
    return cnt;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    long long ans = 0;
    // 枚举所有反转区间，直接模拟反转后的检查数量。
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            ans += count_checked_after_reverse(l, r);
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
