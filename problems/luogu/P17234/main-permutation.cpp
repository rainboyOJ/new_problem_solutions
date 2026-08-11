/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-11 10:52
 * update_at: 2026-08-11 10:52
 */
// main-permutation.cpp：排列特殊性质解法，只适用于 a 是 0..n-1 的一个排列。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n;
int a[MAXN];
int pos[MAXN]; // pos[x] 表示值 x 在排列中的位置

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pos[a[i]] = i;
    }

    long long ans = 0;

    // x = 0：排列中只有一个 0，所有不含 0 的区间都合法。
    int p0 = pos[0];
    ans += 1LL * (p0 - 1) * p0 / 2;
    ans += 1LL * (n - p0) * (n - p0 + 1) / 2;

    int left_bound = pos[0];
    int right_bound = pos[0];

    for (int x = 1; x <= n - 1; x++) {
        int px = pos[x];
        if (left_bound <= px && px <= right_bound) {
            // 值 x 已经落在必须包含的 [L,R] 内，mex 不可能等于 x。
        }
        else if (px < left_bound) {
            ans += 1LL * (left_bound - px) * (n - right_bound + 1);
        }
        else {
            ans += 1LL * left_bound * (px - right_bound);
        }

        if (px < left_bound) left_bound = px;
        if (px > right_bound) right_bound = px;
    }

    cout << ans << '\n';
    return 0;
}
