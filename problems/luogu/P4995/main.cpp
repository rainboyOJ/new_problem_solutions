/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P4995 跳跳！ */
/* 排序后交替跳最高和最低，让相邻高度差尽量大。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;

int n;
int h[MAXN]; // 石头高度

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    // 高度排序
    sort(h + 1, h + n + 1);

    int left = 1, right = n;
    int cur = 0; // 当前所在高度，从地面 0 开始
    long long ans = 0;

    while (left <= right) {
        // 跳到当前最高的石头
        long long diff = h[right] - cur;
        ans += diff * diff;
        cur = h[right];
        right--;

        if (left > right) break;

        // 跳到当前最低的石头
        diff = h[left] - cur;
        ans += diff * diff;
        cur = h[left];
        left++;
    }

    cout << ans << "\n";
    return 0;
}
