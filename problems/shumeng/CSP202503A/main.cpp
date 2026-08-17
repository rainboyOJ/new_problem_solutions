/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:46
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long b, c, l, r;
    cin >> b >> c >> l >> r;

    // 找到区间内第一个偶数坐标作为采样起点
    long long first = l;
    if (first % 2 != 0) first++;

    // 以步长 2 枚举所有偶数坐标点，累加对应函数值
    long long answer = 0;
    for (long long x = first; x <= r; x += 2) {
        answer += x * x + b * x + c;
    }
    // 估算积分等于函数值之和乘以采样间距 2
    cout << answer * 2 << '\n';

    return 0;
}
