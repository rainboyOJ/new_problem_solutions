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
    int n; // 斐波那契数列第 n 项
    cin >> n;
    long long previous = 0; // F(0)
    long long current = 1;  // F(1)
    // 滚动迭代：每次前进一步，previous 变成 current，current 变成两者之和
    for (int i = 0; i < n; i++) {
        long long next = previous + current;
        previous = current;
        current = next;
    }
    // 题目要求以实数形式保留两位小数输出
    printf("%.2f\n", (double)previous);
    return 0;
}
