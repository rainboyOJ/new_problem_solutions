/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
// brute.cpp：小数据暴力解，对每个失效位置逐段模拟能量变化，复杂度 O(n^2)。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<long long> a(n + 1), b(n + 1);
    for (int i = 0; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    // 对每个可能的失效补给位置独立模拟一遍全程
    for (int failure = 1; failure <= n; failure++) {
        long long gain = 0;
        long long answer = 0;

        // gain 表示当前已经发生的净能量变化，answer 是目前必须携带的初始能量
        for (int j = 0; j <= n; j++) {
            answer = max(answer, a[j] - gain);
            gain -= a[j];
            // 第 failure 个补给失效，跳过它，其余补给照常获得
            if (j < n && j + 1 != failure) gain += b[j + 1];
        }

        if (failure > 1) cout << ' ';
        cout << answer;
    }
    cout << '\n';

    return 0;
}
