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
    int n, k; // 范围上限，分类除数
    cin >> n >> k;
    long long sum_a = 0, sum_b = 0; // 倍数的和、非倍数的和
    int cnt_a = 0, cnt_b = 0;       // 倍数的个数、非倍数的个数
    for (int x = 1; x <= n; x++) {
        if (x % k == 0) { // 是 k 的倍数
            sum_a += x;
            cnt_a++;
        } else {
            sum_b += x;
            cnt_b++;
        }
    }
    // 输出两类的平均值，保留 1 位小数
    printf("%.1f %.1f\n", (double)sum_a / cnt_a, (double)sum_b / cnt_b);
    return 0;
}
