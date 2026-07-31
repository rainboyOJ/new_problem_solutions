/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 21:25
 */
// brute.cpp：小数据暴力解，直接计算 Q * K^T 的每个元素。
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

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < d; col++) {
            long long answer = 0;
            for (int other = 0; other < n; other++) {
                long long dot = 0;
                for (int x = 0; x < d; x++) {
                    dot += q[row][x] * k[other][x];
                }
                answer += w[row] * dot * v[other][col];
            }
            cout << answer << (col + 1 == d ? '\n' : ' ');
        }
    }

    return 0;
}
