/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:40
 */
// brute.cpp：小数据暴力解，直接按公式 (W·(Q*K^T))*V 展开计算。
#include <bits/stdc++.h>
using namespace std;

int n, d;
long long q[10005][25];
long long k[10005][25];
long long v[10005][25];
long long w[10005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> d;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++) cin >> q[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++) cin >> k[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < d; j++) cin >> v[i][j];
    for (int i = 0; i < n; i++) cin >> w[i];

    // 按原始公式：答案[row][col] = sum_{other} w[row] * (Q·K^T)[row][other] * V[other][col]
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < d; col++) {
            long long answer = 0;
            for (int other = 0; other < n; other++) {
                long long dot = 0; // Q 第 row 行与 K 第 other 行的内积
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