/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P2249 【深基13.例1】查找 */
/* 在单调不减数组中二分查找目标第一次出现的位置（从 1 开始编号）。 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
const int MAXM = 100005;

int n, m;
int a[MAXN]; // 单调不减数组

// 二分查找 value 第一次出现的位置，不存在返回 -1
int first_pos(int value) {
    int l = 1, r = n, ans = -1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (a[mid] >= value) {
            if (a[mid] == value) ans = mid;
            r = mid - 1; // 继续向左找第一次出现
        } else {
            l = mid + 1;
        }
    }
    return ans;
}

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= m; i++) {
        int q;
        cin >> q;
        cout << first_pos(q) << " \n"[i == m];
    }
    return 0;
}
