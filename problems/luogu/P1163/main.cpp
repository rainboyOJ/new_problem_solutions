/**
 * Author by Rainboy blog: https://rainboylv.com github: https://rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */

/* P1163 银行贷款 */
/* 二分月利率，逐月模拟还款后剩余本金，使最终余额接近零。 */

#include <bits/stdc++.h>
using namespace std;

double principal; // 本金
double payment;   // 每月还款额
int months;       // 还清月数

// 给定月利率 rate（小数），计算最终剩余本金
double remaining(double rate) {
    double balance = principal;
    for (int i = 1; i <= months; i++) {
        balance = balance * (1 + rate) - payment;
    }
    return balance;
}

int main() {
    cin >> principal >> payment >> months;

    // 利率越高，最终剩余本金越大，单调递增
    double l = 0.0, r = 3.0;
    // 浮点二分固定 100 次，精度足够
    for (int i = 1; i <= 100; i++) {
        double mid = (l + r) / 2;
        if (remaining(mid) <= 0) {
            l = mid; // 利率还能更高
        } else {
            r = mid;
        }
    }

    // 输出百分数，保留一位小数
    printf("%.1f\n", l * 100);
    return 0;
}
