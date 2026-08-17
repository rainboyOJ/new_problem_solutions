/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
// brute.cpp：小数据暴力解，枚举每个像素邻域中的全部格子，直接求和再比较均值。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 605;

int n, levels, radius, threshold;
int image[MAXN][MAXN];   // 原始灰度矩阵

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> levels >> radius >> threshold;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) cin >> image[i][j];
    }

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            // 对每个像素，枚举其邻域内的所有格子求和
            int total = 0, count = 0;
            for (int x = max(1, i - radius); x <= min(n, i + radius); x++) {
                for (int y = max(1, j - radius); y <= min(n, j + radius); y++) {
                    total += image[x][y];
                    count++;
                }
            }
            if (total <= threshold * count) answer++;
        }
    }
    cout << answer << '\n';
    return 0;
}