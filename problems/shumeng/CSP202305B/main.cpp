/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 21:25
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, d;
    cin >> n >> d;

    vector<vector<long long> > q(n, vector<long long>(d));
    vector<vector<long long> > k(n, vector<long long>(d));
    vector<vector<long long> > v(n, vector<long long>(d));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) cin >> q[i][j];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) cin >> k[i][j];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < d; j++) cin >> v[i][j];
    }

    vector<long long> w(n);
    for (int i = 0; i < n; i++) cin >> w[i];

    // 先计算 K^T * V，结果只有 d*d 个元素。
    vector<vector<long long> > middle(d, vector<long long>(d, 0));
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            for (int row = 0; row < n; row++) {
                middle[i][j] += k[row][i] * v[row][j];
            }
        }
    }

    // W 只会缩放 Q 的每一行，再乘上上面的 d*d 矩阵。
    for (int row = 0; row < n; row++) {
        for (int j = 0; j < d; j++) {
            long long answer = 0;
            for (int i = 0; i < d; i++) {
                answer += w[row] * q[row][i] * middle[i][j];
            }
            cout << answer << (j + 1 == d ? '\n' : ' ');
        }
    }

    return 0;
}
