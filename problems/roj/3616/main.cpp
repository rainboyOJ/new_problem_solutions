/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 15:14
 * update_at: 2026-10-06 15:14
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

ll n, i, j;

// 计算 (row, col) 在螺旋矩阵中的值，利用圈层分解，O(1) 定位
ll spiral_value(ll row, ll col) {
    // 圈层号 k：到四条边界的最近距离，外圈为 0
    ll k = min(row - 1, min(col - 1, min(n - row, n - col)));
    // 前 k 层完整圈的格子总数
    ll full = 0;
    for (ll m = 0; m < k; ++m) {
        full += 4 * (n - 2 * m) - 4;
    }
    // 第 k 层的边长与上边格数（不含转角）
    ll side = n - 2 * k;
    ll top = side - 1;
    // 判断目标格落在第 k 层的哪条边上，累加段内偏移
    ll offset;
    if (row - 1 == k) {          // 上边，从左到右
        offset = col - (k + 1);
    } else if (n - col == k) {   // 右边，从上到下
        offset = top + (row - (k + 1));
    } else if (n - row == k) {   // 下边，从右到左
        offset = 2 * top + (n - k - col);
    } else {                     // 左边，从下到上
        offset = 3 * top + (n - k - row);
    }
    return full + offset + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> i >> j;
    cout << spiral_value(i, j) << '\n';
    return 0;
}
