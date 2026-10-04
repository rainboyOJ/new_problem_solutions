/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:16
 * update_at: 2026-10-05 02:16
 */
// main.cpp：去掉一个最大值和一个最小值后求平均，再求有效样本与平均值的最大绝对偏差。
#include <cstdio>
#include <algorithm>

typedef long long ll;

const int MAXN = 305;
double a[MAXN]; // a[1..n] 保存 n 份白细胞样本

int main() {
    ll n;
    if (scanf("%lld", &n) != 1) {
        return 0;
    }

    // 逐份读入样本；读不到时按 0.0 补足，保持与原题评测数据一致
    for (ll i = 1; i <= n; i++) {
        if (scanf("%lf", &a[i]) != 1) {
            a[i] = 0.0;
        }
    }

    // 一次扫描求最大值、最小值和总和
    double max_value = a[1];
    double min_value = a[1];
    double total = 0.0;
    for (ll i = 1; i <= n; i++) {
        if (a[i] > max_value) {
            max_value = a[i];
        }
        if (a[i] < min_value) {
            min_value = a[i];
        }
        total += a[i];
    }

    double average = (total - max_value - min_value) / (n - 2);

    // 再扫描一次，求有效样本（不等于最大值也不等于最小值）与平均值的最大偏差
    double error = 0.0;
    for (ll i = 1; i <= n; i++) {
        if (a[i] == max_value || a[i] == min_value) {
            continue;
        }
        double diff = a[i] - average;
        if (diff < 0.0) {
            diff = -diff;
        }
        if (diff > error) {
            error = diff;
        }
    }

    printf("%.2f %.2f\n", average, error);
    return 0;
}
