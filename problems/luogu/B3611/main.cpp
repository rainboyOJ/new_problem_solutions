/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-17 01:40
 * update_at: 2026-07-17 01:40
 */
// Floyd(Warshall) 求传递闭包：reach[i][j] 表示 i 能否到达 j
// 中转点 k 必须在最外层，顺序不能换
#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int n;
bool reach[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            int x;
            cin >> x;
            reach[i][j] = (x == 1);
        }

    for (int k = 1; k <= n; k++)                 // 中转点
        for (int i = 1; i <= n; i++) {
            if (!reach[i][k]) continue;          // i 到不了 k，松弛无意义
            for (int j = 1; j <= n; j++)
                if (reach[k][j]) reach[i][j] = true;
        }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j > 1) cout << ' ';
            cout << (reach[i][j] ? 1 : 0);
        }
        cout << '\n';
    }

    return 0;
}
