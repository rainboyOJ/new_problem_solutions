/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

int n;
double a[MAXN];   // 原始整数数据
double average;   // 平均值
double variance;  // 方差

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        average += a[i];
    }
    average /= n;

    // 按定义累加平方偏差，得到方差 D(a)
    for (int i = 0; i < n; i++) {
        variance += (a[i] - average) * (a[i] - average);
    }
    variance /= n;

    // 归一化公式：f(a[i]) = (a[i]-均值) / 标准差
    double deviation = sqrt(variance);
    cout << setprecision(17);
    for (int i = 0; i < n; i++) {
        cout << (a[i] - average) / deviation << '\n';
    }

    return 0;
}