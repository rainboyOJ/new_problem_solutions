/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 23:00
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, limit;
    cin >> n >> limit;
    vector<vector<int> > image(n, vector<int>(n)); // 灰度图像
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) cin >> image[i][j];
    }

    // CSP 水印图案：1 表示白色(灰度>=k)，0 表示黑色(灰度<k)
    int pattern[5][9] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 1, 0, 0, 1, 0, 1},
        {1, 0, 0, 1, 1, 1, 1, 1, 0},
        {1, 0, 0, 0, 0, 1, 1, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 0, 0},
    };

    // 差分数组：difference[k] 表示阈值 k 的覆盖次数变化量
    vector<int> difference(limit + 2, 0);
    for (int top = 0; top + 5 <= n; top++) {
        for (int left = 0; left + 9 <= n; left++) {
            // 该窗口能呈现水印的阈值区间：[黑色位置最大灰度+1, 白色位置最小灰度]
            int minimum_white = limit;
            int maximum_black = -1;
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 9; j++) {
                    if (pattern[i][j] == 1) {
                        minimum_white = min(minimum_white, image[top + i][left + j]);
                    } else {
                        maximum_black = max(maximum_black, image[top + i][left + j]);
                    }
                }
            }
            int lower = maximum_black + 1;
            int upper = minimum_white;
            if (lower <= upper) {
                difference[lower]++;
                difference[upper + 1]--;
            }
        }
    }

    // 前缀和求每个阈值被覆盖的次数，大于 0 即可检测出水印
    int active = 0;
    for (int k = 0; k < limit; k++) {
        active += difference[k];
        if (active > 0) cout << k << '\n';
    }
    return 0;
}
