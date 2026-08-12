/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 22:09
 * update_at: 2026-08-12 22:09
 */
// brute.cpp：小数据暴力解，O(n^3) 三重循环直接枚举所有 i<j<k，
// 检查 a[i] < a[j] < a[k] 是否成立，天然符合题意，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 30005;

int n;
int a[MAXN]; // 输入序列

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 三重循环直接枚举三元组 (i, j, k)，满足 i<j<k 且值严格递增。
    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            for (int k = j + 1; k <= n; k++) {
                if (a[i] < a[j] && a[j] < a[k]) {
                    ans++;
                }
            }
        }
    }
    cout << ans << '\n';

    return 0;
}
