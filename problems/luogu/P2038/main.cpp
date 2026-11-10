/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 01:45
 * update_at: 2026-11-11 01:45
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int GRID_SIZE = 129;
int val[GRID_SIZE + 5][GRID_SIZE + 5];
int prefix_sum[GRID_SIZE + 5][GRID_SIZE + 5];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int d, n;
    if (!(cin >> d >> n)) return 0;

    for (int i = 0; i < n; ++i) {
        int x, y, k;
        cin >> x >> y >> k;
        // 坐标平移 1 位映射到 [1, 129]
        val[x + 1][y + 1] = k;
    }

    // 计算二维前缀和
    for (int i = 1; i <= GRID_SIZE; ++i) {
        for (int j = 1; j <= GRID_SIZE; ++j) {
            prefix_sum[i][j] = prefix_sum[i - 1][j] + prefix_sum[i][j - 1] -
                               prefix_sum[i - 1][j - 1] + val[i][j];
        }
    }

    int max_covered = -1;
    int way_count = 0;

    // 枚举所有可能的安装路口 (x, y) 从 0 到 128
    for (int x = 0; x < GRID_SIZE; ++x) {
        for (int y = 0; y < GRID_SIZE; ++y) {
            // 裁剪正方形覆盖边界
            int x1 = max(0, x - d) + 1;
            int x2 = min(GRID_SIZE - 1, x + d) + 1;
            int y1 = max(0, y - d) + 1;
            int y2 = min(GRID_SIZE - 1, y + d) + 1;

            int cur = prefix_sum[x2][y2] - prefix_sum[x1 - 1][y2] -
                      prefix_sum[x2][y1 - 1] + prefix_sum[x1 - 1][y1 - 1];

            if (cur > max_covered) {
                max_covered = cur;
                way_count = 1;
            } else if (cur == max_covered) {
                way_count++;
            }
        }
    }

    cout << way_count << " " << max_covered << "\n";

    return 0;
}
