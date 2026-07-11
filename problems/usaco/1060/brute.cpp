/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:58
 * update_at: 2026-07-11 13:59
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
int p[MAXN]; // p[i] 表示第 i 朵花的花瓣数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }

    int ans = 0;

    // 枚举每一张照片 [l, r]，再检查照片内是否有一朵花等于平均值。
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            int sum = 0;
            for (int k = l; k <= r; k++) {
                sum += p[k];
            }

            int len = r - l + 1;
            bool ok = false;
            for (int k = l; k <= r; k++) {
                if (p[k] * len == sum) {
                    ok = true;
                }
            }

            if (ok) {
                ans++;
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
