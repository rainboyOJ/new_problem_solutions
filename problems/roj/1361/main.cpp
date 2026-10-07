/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:00
 * update_at: 2026-10-05 12:00
 */

#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

bool reach[10][10]; // reach[d][v] = 1 表示数字 d 经任意次变换能得到 v

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string n;
    int k;
    if (!(cin >> n)) return 0;
    cin >> k;

    // 初始化：每个数字能到达自身
    for (int d = 0; d < 10; ++d) reach[d][d] = true;

    for (int i = 0; i < k; ++i) {
        int x, y;
        cin >> x >> y;
        reach[x][y] = true; // 直接规则 x -> y
    }

    // Floyd 求传递闭包：10 个节点的有向图
    for (int mid = 0; mid < 10; ++mid)
        for (int d = 0; d < 10; ++d)
            if (reach[d][mid])
                for (int v = 0; v < 10; ++v)
                    if (reach[mid][v])
                        reach[d][v] = true;

    // 每位独立，乘法原理计数
    ll ans = 1;
    for (char c : n) {
        int d = c - '0';
        int cnt = 0;
        for (int v = 0; v < 10; ++v)
            if (reach[d][v]) ++cnt;
        ans *= cnt;
    }

    cout << ans << "\n";
    return 0;
}
