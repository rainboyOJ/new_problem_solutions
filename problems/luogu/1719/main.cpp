/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-16 17:48
 * update_at: 2026-07-19 17:29
 */
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 125;

int n;
int matrix[MAX_N][MAX_N];
int column_sum[MAX_N]; // 当前上下边界之间，每一列的元素和

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

    for (int top = 1; top <= n; top++) {
        memset(column_sum, 0, sizeof(column_sum));

        for (int bottom = top; bottom <= n; bottom++) {
            int current = 0; // 必须以当前列结尾的最大连续子段和

            for (int column = 1; column <= n; column++) {
                column_sum[column] += matrix[bottom][column];

                // 要么从当前列重新开始，要么接在前一列的最优子段后面。
                current = max(current, 0) + column_sum[column];
                answer = max(answer, current);
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
