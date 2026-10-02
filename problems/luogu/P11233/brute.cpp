/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:57
 * update_at: 2026-10-01 22:57
 */
// brute.cpp：小数据暴力解，枚举所有染色方案并逐个计算得分。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 25;   // 暴力只服务小数据，n 取到 20 左右（要枚举 2^n 种方案）

int T, n;
int a[MAXN];

// 按 mask 的每一位决定第 i 个数染哪种颜色，逐个算出贡献。
ll calc_score(int mask) {
    int last[2];
    last[0] = last[1] = 0;   // 每种颜色还没出现过时，最后值记作 0

    ll score = 0;
    for (int i = 1; i <= n; i++) {
        int color = (mask >> (i - 1)) & 1;

        // 左边最近的同色数就是该颜色的最后值；相等才得 A_i 分。
        if (last[color] == a[i]) {
            score += a[i];
        }
        last[color] = a[i];
    }

    return score;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }

        ll ans = 0;
        int total = 1 << n;
        for (int mask = 0; mask < total; mask++) {
            ans = max(ans, calc_score(mask));
        }

        cout << ans << '\n';
    }

    return 0;
}
