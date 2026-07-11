/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:20
 * update_at: 2026-07-11 15:23
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int n;
int a[MAXN];
int cnt_left[MAXN];   // 已经扫过的前缀中，每个值出现了多少次。
int cnt_right[MAXN];  // 当前及右侧后缀中，每个值还剩多少次。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        cnt_right[a[i]]++;
    }

    long long ans = 0;
    int distinct_left = 0; // 左侧出现过的不同数的个数。

    for (int i = 1; i <= n; i++) {
        int x = a[i];

        // 如果从当前位置到右侧刚好还剩两个 x，那么 i 可以作为 moo 中第一个 o。
        if (cnt_right[x] == 2) {
            ans += distinct_left;
            if (cnt_left[x] > 0) {
                ans--; // m 不能等于 o，排除左侧出现过的 x。
            }
        }

        cnt_right[x]--;
        if (cnt_left[x] == 0) {
            distinct_left++;
        }
        cnt_left[x]++;
    }

    cout << ans << '\n';

    return 0;
}
