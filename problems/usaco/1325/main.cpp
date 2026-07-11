/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:40
 * update_at: 2026-07-11 16:41
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n, k;
long long T;
int active_pos[MAXN];
int ans[MAXN];

long long mod_positive(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> T;
    for (int i = 1; i <= k; i++) {
        cin >> active_pos[i];
    }
    active_pos[k + 1] = n;

    for (int i = 1; i <= k; i++) {
        int left = active_pos[i];
        int right = active_pos[i + 1];
        int len = right - left;

        for (int cow = left; cow < right; cow++) {
            int offset = cow - left;

            // 固定活动点视角下，区间内部每分钟向左循环移动一次。
            long long new_offset = mod_positive((long long)offset - T, len);
            int final_pos = (int)((left + new_offset + T) % n);
            ans[final_pos] = cow;
        }
    }

    for (int i = 0; i < n; i++) {
        if (i > 0) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';

    return 0;
}
