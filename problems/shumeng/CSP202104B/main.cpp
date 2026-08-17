/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 605;

int n, levels, radius, threshold;
int sum[MAXN][MAXN];   // sum[i][j] 为以 (1,1) 到 (i,j) 为对角矩形的像素总和

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> levels >> radius >> threshold;
    // 边读入边构造二维前缀和
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int value;
            cin >> value;
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + value;
        }
    }

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            // 邻域在图像边界处裁剪为矩形
            int top = max(1, i - radius), bottom = min(n, i + radius);
            int left = max(1, j - radius), right = min(n, j + radius);
            int total = sum[bottom][right] - sum[top - 1][right] - sum[bottom][left - 1] + sum[top - 1][left - 1];
            int count = (bottom - top + 1) * (right - left + 1);
            // 用乘法比较避免浮点误差：均值 <= t 等价于 总和 <= t * 个数
            if (total <= threshold * count) answer++;
        }
    }
    cout << answer << '\n';
    return 0;
}