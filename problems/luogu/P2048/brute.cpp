/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05
 * update_at: 2026-08-05
 */
// brute.cpp：小数据暴力解，枚举所有合法超级和弦，排序取前 k 个。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, L, R;
    cin >> n >> k >> L >> R;

    vector<long long> a(n + 1), S(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        S[i] = S[i - 1] + a[i];
    }

    // 枚举所有合法超级和弦的和
    vector<long long> sums;
    for (int i = 1; i <= n; i++) {
        int left = i + L - 1;
        int right = min(i + R - 1, n);
        for (int j = left; j <= right; j++)
            sums.push_back(S[j] - S[i - 1]);
    }

    // 降序排序，取前 k 个
    sort(sums.rbegin(), sums.rend());

    long long ans = 0;
    for (int i = 0; i < k; i++)
        ans += sums[i];

    cout << ans << "\n";
    return 0;
}
