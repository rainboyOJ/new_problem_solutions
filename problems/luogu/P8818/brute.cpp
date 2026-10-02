/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-21 14:48
 * update_at: 2026-10-01 22:20
 */
// brute.cpp：小数据暴力解，枚举小 L 选哪个 x，再枚举小 Q 选哪个 y，直接按题意做极大极小。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF64 = (1LL << 60); // 哨兵值，比任何真实答案都小/大

int n, m, q;
ll a[205]; // 数组 A，只服务小数据
ll b[205]; // 数组 B，只服务小数据

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++) {
        cin >> b[i];
    }

    while (q--) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;

        // 外层枚举小 L 的选择 x，内层求小 Q 能压到的最小得分，再取最大
        ll answer = -INF64;
        for (int x = l1; x <= r1; x++) {
            ll worst = INF64;
            for (int y = l2; y <= r2; y++) {
                worst = min(worst, a[x] * b[y]);
            }
            answer = max(answer, worst);
        }
        cout << answer << '\n';
    }

    return 0;
}
