/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 16:11
 * update_at: 2026-07-11 16:12
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
long long a[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    long long ans = 0;

    // 小数据朴素模拟：从左到右把当前位置修成 0，并直接更新后缀。
    for (int i = 1; i <= n; i++) {
        long long op = -a[i];
        ans += llabs(op);

        for (int j = i; j <= n; j++) {
            a[j] += op * (j - i + 1);
        }
    }

    cout << ans << '\n';

    return 0;
}
