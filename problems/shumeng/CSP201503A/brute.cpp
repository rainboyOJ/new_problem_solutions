/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:50
 */
// brute.cpp：小数据基准，显式构造旋转后的矩阵。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int> > image(n, vector<int>(m));
    vector<vector<int> > rotated(m, vector<int>(n));
    for (int row = 0; row < n; row++) {
        for (int column = 0; column < m; column++) {
            cin >> image[row][column];
            rotated[m - 1 - column][row] = image[row][column];
        }
    }

    for (int row = 0; row < m; row++) {
        for (int column = 0; column < n; column++) {
            if (column > 0) cout << ' ';
            cout << rotated[row][column];
        }
        cout << '\n';
    }

    return 0;
}
