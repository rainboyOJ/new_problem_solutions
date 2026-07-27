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
    // 遍历数组找最小值
    int min_val = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] < min_val) {
            min_val = a[i];
        }
    }
    cout << min_val << endl;
    return 0;
}
