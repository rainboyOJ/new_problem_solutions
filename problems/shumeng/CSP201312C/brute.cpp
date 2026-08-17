/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:46
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
long long h[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    long long ans = 0;
    // 枚举矩形覆盖的连续区间 [left, right]。
    for (int left = 1; left <= n; left++) {
        long long lowest = h[left];
        for (int right = left; right <= n; right++) {
            lowest = min(lowest, h[right]);
            long long area = lowest * (right - left + 1);
            ans = max(ans, area);
        }
    }

    cout << ans << '\n';
    return 0;
}
