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
    double t; // 饮料总量（毫升）
    int n;    // 同学人数
    cin >> t >> n;
    // 第一行：每人分到的饮料，保留 3 位小数
    printf("%.3f\n", t / n);
    // 第二行：每人需要 2 个杯子，共需要 n * 2 个
    cout << n * 2 << endl;
    return 0;
}
