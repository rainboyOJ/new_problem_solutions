/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 14:11
 * update_at: 2026-07-11 14:13
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
int x[MAXN], y[MAXN]; // 第 i 个柱子的坐标

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    long long ans = 0;

    // 枚举 i 为直角顶点，j 提供水平边，k 提供竖直边。
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j || y[i] != y[j]) {
                continue;
            }

            for (int k = 1; k <= n; k++) {
                if (i == k || x[i] != x[k]) {
                    continue;
                }

                long long base = llabs(x[j] - x[i]);
                long long height = llabs(y[k] - y[i]);
                long long area2 = base * height;
                if (ans < area2) {
                    ans = area2;
                }
            }
        }
    }

    cout << ans << '\n';

    return 0;
}
