/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 14:30
 * update_at: 2026-08-05 14:30
 */
// brute.cpp：小数据暴力解，O(n^2) 枚举所有点对按公式直接计算。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20005;

int n;
long long v[MAXN], x[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> v[i] >> x[i];

    long long ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++) {
            long long dist = x[i] - x[j];
            if (dist < 0) dist = -dist;
            ans += max(v[i], v[j]) * dist;
        }

    cout << ans << '\n';

    return 0;
}
