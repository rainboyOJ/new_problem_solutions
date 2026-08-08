/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

#include <bits/stdc++.h>
using namespace std;

int a[10005]; // 保存冰雹序列
int cnt;      // 序列长度

int main() {
    int n;
    cin >> n;
    // 先把起始数存入
    a[++cnt] = n;
    // 按规则模拟，直到变成 1
    while (n != 1) {
        if (n % 2 == 1) // 奇数：3n+1
            n = n * 3 + 1;
        else            // 偶数：n/2
            n /= 2;
        a[++cnt] = n;
    }
    // 题目要求倒序输出（从 1 开始）
    for (int i = cnt; i >= 1; i--) cout << a[i] << " ";
    return 0;
}
