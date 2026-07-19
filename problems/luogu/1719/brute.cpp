/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-16 17:48
 * update_at: 2026-07-19 17:39
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 125;

int n;
int matrix[MAX_N][MAX_N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> matrix[i][j];
        }
    }

    int answer = INT_MIN;

    // 直接枚举矩形的四条边，再逐格计算矩形和，只适合小数据。
    for (int top = 1; top <= n; top++) {
        for (int bottom = top; bottom <= n; bottom++) {
            for (int left = 1; left <= n; left++) {
                for (int right = left; right <= n; right++) {
                    int sum = 0;
                    for (int i = top; i <= bottom; i++) {
                        for (int j = left; j <= right; j++) {
                            sum += matrix[i][j];
                        }
                    }
                    answer = max(answer, sum);
                }
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
