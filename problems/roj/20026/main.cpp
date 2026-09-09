/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-06 15:54
 * update_at: 2026-09-06 15:57
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;

int n;
char s[MAXN];
int preA[MAXN]; // preA[i] 表示前 i 位中 A 的个数
int preB[MAXN]; // preB[i] 表示前 i 位中 B 的个数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> (s + 1);
    n = strlen(s + 1);

    // 前缀计数：preA[i]、preB[i]
    for (int i = 1; i <= n; i++) {
        preA[i] = preA[i - 1] + (s[i] == 'A');
        preB[i] = preB[i - 1] + (s[i] == 'B');
    }

    // 枚举最终形态：前 p 位全 A，后 n-p 位全 B
    int ans = n;
    for (int p = 0; p <= n; p++) {
        // 前 p 位里的 B 要翻成 A；后 n-p 位里的 A 要翻成 B
        int cost = preB[p] + (preA[n] - preA[p]);
        ans = min(ans, cost);
    }

    cout << ans << "\n";
    return 0;
}
