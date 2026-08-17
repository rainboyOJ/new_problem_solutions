/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-17 23:05
 */
#include <bits/stdc++.h>
using namespace std;

// 单次 3 位变换 f(x,k)，x 与 k 均小于 2^3
int f_value(int x, int k) {
    return (((x * x + k * k) & 7) ^ k);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> k(m); // 参数序列
    for (int i = 0; i < m; i++) cin >> k[i];

    // 9 位状态只有 512 种：枚举所有初始值，正向模拟得到输出并建立逆映射
    vector<int> inverse(512, -1);
    for (int start = 0; start < 512; start++) {
        int value = start;
        for (int step_index = 0; step_index < m; step_index++) {
            int step = k[step_index];
            // 把 9 位拆成高、中、低三组 3 位数字 a,b,c
            int a = (value >> 6) & 7;
            int b = (value >> 3) & 7;
            int c = value & 7;
            // 题目给定的 g 变换：
            // 新 a = b，新 b = c ^ f(b,k)，新 c = a ^ f(c,k)
            int na = b;
            int nb = c ^ f_value(b, step);
            int nc = a ^ f_value(c, step);
            value = (na << 6) | (nb << 3) | nc;
        }
        inverse[value] = start; // 题目保证每个输出只对应唯一输入
    }

    // 每个查询直接查表恢复输入
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        if (i) cout << ' ';
        cout << inverse[value];
    }
    cout << '\n';
    return 0;
}
