/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

// 递归计算阶乘：n! = n * (n-1)!
int fact(int n) {
    if (n == 1) return 1;      // 终止条件
    return n * fact(n - 1);    // 递归调用
}

int main() {
    int n;
    cin >> n;
    cout << fact(n);
    return 0;
}
