/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 23:34
 */
// brute.cpp：直接维护二维矩阵，逐项完成重塑、转置和查询。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, operation_count;
    cin >> n >> m >> operation_count;
    vector<vector<int> > matrix(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> matrix[i][j];
    }

    while (operation_count--) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) {
            vector<int> value;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) value.push_back(matrix[i][j]);
            }
            matrix.assign(x, vector<int>(y));
            for (int i = 0; i < x; i++) {
                for (int j = 0; j < y; j++) matrix[i][j] = value[i * y + j];
            }
            n = x;
            m = y;
        } else if (type == 2) {
            vector<vector<int> > transposed(m, vector<int>(n));
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) transposed[j][i] = matrix[i][j];
            }
            matrix.swap(transposed);
            swap(n, m);
        } else {
            cout << matrix[x][y] << '\n';
        }
    }

    return 0;
}
