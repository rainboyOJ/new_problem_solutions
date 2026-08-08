/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int a[105]; // 存储输入的数字（不含末尾的 0）
int n;      // 数字个数

int main() {
    int x;
    // 读到 0 为止，0 不存入数组
    while (cin >> x) {
        if (x == 0) break;
        a[++n] = x;
    }
    // 倒序输出
    for (int i = n; i >= 1; i--) cout << a[i] << " ";
    return 0;
}
