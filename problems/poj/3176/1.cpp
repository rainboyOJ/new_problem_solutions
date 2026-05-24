#include <iostream>
#include <algorithm> // for max
#include <vector>

using namespace std;

// 定义最大行数，稍微大一点防止越界
const int MAXN = 355;
int grid[MAXN][MAXN];

int main() {
    // 优化 I/O 速度
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    // 1. 读取输入
    // 我们使用 1-based indexing (从下标1开始)，方便对应行号
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= i; ++j) {
            cin >> grid[i][j];
        }
    }

    // 2. 动态规划 (自底向上)
    // 从倒数第二行开始 (i = N-1)，一直向上处理到第 1 行
    // 每一行的第 j 个元素，看它下一行(i+1)的第 j 个和第 j+1 个，谁大选谁
    for (int i = N - 1; i >= 1; --i) {
        for (int j = 1; j <= i; ++j) {
            // 状态转移方程
            grid[i][j] += max(grid[i+1][j], grid[i+1][j+1]);
        }
    }

    // 3. 输出结果
    // 经过计算，grid[1][1] 存储的就是从顶到底的最大路径和
    cout << grid[1][1] << endl;

    return 0;
}
