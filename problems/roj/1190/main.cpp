/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:48
 * update_at: 2026-10-05 04:48
 */

#include <iostream>
using namespace std;

typedef long long ll;

// 打表：w[0..70]，w[i] 表示上 i 阶的走法数
// 递推：w(n) = w(n-1) + w(n-2) + w(n-3)，边界 w(0)=1, w(1)=1, w(2)=2
const int MAXN = 71;       // 题目要求 0 < n < 71
ll w[MAXN];

int main() {
    // 初始化边界
    w[0] = 1;               // 空走法
    w[1] = 1;
    w[2] = 2;
    // 从小到大递推填表，每格只依赖前三个
    for (int i = 3; i < MAXN; i++) {
        w[i] = w[i - 1] + w[i - 2] + w[i - 3];
    }

    // 多组询问，每行一个 n，遇到 0 结束
    int n;
    while (cin >> n && n != 0) {
        cout << w[n] << "\n";
    }
    return 0;
}