/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:35
 * update_at: 2026-11-11 00:35
 */

#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    int k = 1;
    // 逐层减去前面各条对角线的项数
    while (n > k) {
        n -= k;
        k++;
    }

    // 此时 k 为所在对角线编号，n 为当前对角线上的相对位置
    int numerator = 0;   // 分子
    int denominator = 0; // 分母

    if (k % 2 == 1) {
        // 奇数层：从下往上走，分子递减，分母递增
        numerator = k - n + 1;
        denominator = n;
    } else {
        // 偶数层：从上往下走，分子递增，分母递减
        numerator = n;
        denominator = k - n + 1;
    }

    cout << numerator << "/" << denominator << "\n";

    return 0;
}
