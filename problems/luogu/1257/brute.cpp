/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 13:00
 * update_at: 2026-08-05 13:00
 */
// brute.cpp：小数据暴力解，O(n^2) 枚举所有点对取最小距离。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int n;
long long x[MAXN], y[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> x[i] >> y[i];

    double ans = 1e100;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
            long long dx = x[i] - x[j], dy = y[i] - y[j];
            ans = min(ans, sqrt((double)(dx * dx + dy * dy)));
        }

    cout << fixed << setprecision(4) << ans << '\n';

    return 0;
}
