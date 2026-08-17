/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:41
 */
// brute.cpp：小数据暴力解，枚举两人的每一对装车区间，累加交集长度。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;

int n;
int left_h[MAXN], right_h[MAXN];   // 小 H 的装车时间段
int left_w[MAXN], right_w[MAXN];   // 小 W 的装车时间段

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

    // 枚举所有区间对，交集长度取 max(0, min(r1,r2) - max(l1,l2))。
    int answer = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int overlap_left = max(left_h[i], left_w[j]);
            int overlap_right = min(right_h[i], right_w[j]);
            if (overlap_left < overlap_right) {
                answer += overlap_right - overlap_left;
            }
        }
    }
    cout << answer << '\n';

    return 0;
}