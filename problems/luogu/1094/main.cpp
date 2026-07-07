/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * date: 2026-07-07 00:00:00
 */
// main.cpp：贪心 + 排序 + 双指针，O(n log n)。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30005;

int w, n;
int p[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> w >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    // 按价格从小到大排序
    sort(p + 1, p + n + 1);

    int ans = 0;
    int l = 1, r = n;

    while (l <= r) {
        if (l == r) {
            // 只剩一个，独立一组
            ans++;
            break;
        }
        if (p[l] + p[r] <= w) {
            // 最小的和最大的可以配成一组
            l++;
            r--;
        } else {
            // 最大的只能独立一组
            r--;
        }
        ans++;
    }

    cout << ans << '\n';
    return 0;
}
