/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:50
 */
#include <bits/stdc++.h>
using namespace std;

int image[1005][1005]; // 原始图像矩阵

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    for (int row = 0; row < n; row++) {
        for (int column = 0; column < m; column++) {
            cin >> image[row][column];
        }
    }

    // 原矩阵从最右列到最左列依次成为旋转后的每一行。
    for (int column = m - 1; column >= 0; column--) {
        for (int row = 0; row < n; row++) {
            if (row > 0) cout << ' ';
            cout << image[row][column];
        }
        cout << '\n';
    }

    return 0;
}
