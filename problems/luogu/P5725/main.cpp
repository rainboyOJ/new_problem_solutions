/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    int value = 1;
    // 输出 n×n 的数字正方形
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            printf("%02d", value);
            value++;
        }
        cout << endl;
    }
    cout << endl; // 两个图形之间的空行
    // 输出右对齐的数字三角形
    value = 1;
    for (int row = 1; row <= n; row++) {
        // 右对齐：每一行前面补 (n-row) 个"  "（每个数字占两位）
        for (int i = 0; i < n - row; i++) {
            cout << "  ";
        }
        for (int i = 0; i < row; i++) {
            printf("%02d", value);
            value++;
        }
        cout << endl;
    }
    return 0;
}
