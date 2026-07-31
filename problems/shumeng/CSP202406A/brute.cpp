/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 23:31
 */
// brute.cpp：直观模拟，把矩阵先展平成一维数组，再按新形状输出。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, p, q;
    cin >> n >> m >> p >> q;
    vector<vector<int> > matrix(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> matrix[i][j];
    }

    vector<int> value;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) value.push_back(matrix[i][j]);
    }
    for (int i = 0; i < p; i++) {
        for (int j = 0; j < q; j++) {
            if (j > 0) cout << ' ';
            cout << value[i * q + j];
        }
        cout << '\n';
    }

    return 0;
}
