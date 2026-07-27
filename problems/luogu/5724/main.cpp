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
    int n; // 整数的个数
    cin >> n;
    int a[1005]; // 存储 n 个整数
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    // 扫描数组同时找最大值和最小值
    int max_val = a[0], min_val = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max_val) max_val = a[i];
        if (a[i] < min_val) min_val = a[i];
    }
    // 极差 = 最大值 - 最小值
    cout << max_val - min_val << endl;
    return 0;
}
