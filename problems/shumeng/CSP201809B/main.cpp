/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:41
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;

int n;
int left_h[MAXN], right_h[MAXN];   // 小 H 的装车时间段 [left_h[i], right_h[i]]
int left_w[MAXN], right_w[MAXN];   // 小 W 的装车时间段 [left_w[i], right_w[i]]

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> left_h[i] >> right_h[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> left_w[i] >> right_w[i];
    }

    // 两段区间 [l1,r1] 与 [l2,r2] 的交集长度为 max(l1,l2)..min(r1,r2) 的长度。
    int answer = 0;
    int i = 1, j = 1;
    while (i <= n && j <= n) {
        int overlap_left = max(left_h[i], left_w[j]);
        int overlap_right = min(right_h[i], right_w[j]);
        if (overlap_left < overlap_right) {
            answer += overlap_right - overlap_left;
        }

        // 结束时刻更早的一方不可能再和对方的后续区间相交，推进它。
        if (right_h[i] < right_w[j]) {
            i++;
        } else {
            j++;
        }
    }
    cout << answer << '\n';

    return 0;
}