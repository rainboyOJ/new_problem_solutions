/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

int n, d;
long long q[10005][25]; // Q 矩阵
long long k[10005][25]; // K 矩阵
long long v[10005][25]; // V 矩阵
long long w[10005];     // 权重向量 W
long long middle[25][25]; // K^T * V 的结果矩阵

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

    // 利用结合律 (W·Q)*K^T*V = (W·Q)*(K^T*V)
    // 先计算 K^T * V，结果只有 d*d 个元素，避免 n*n 的中间矩阵
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            long long sum = 0;
            for (int row = 0; row < n; row++) {
                sum += k[row][i] * v[row][j];
            }
            middle[i][j] = sum;
        }
    }

    // W 只按行缩放 Q，再与 d*d 矩阵相乘得到最终结果
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