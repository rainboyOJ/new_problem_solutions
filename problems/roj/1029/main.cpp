/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:52
 * update_at: 2026-10-04 22:52
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

double a, b; // 输入：两个双精度浮点数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> a >> b;

    // fmod(a, b) 按 IEEE-754 定义给出精确余数 r，满足 a = k*b + r 且 0 <= r < |b|
    double r = fmod(a, b);

    // cout 默认精度为 6 位有效数字，与题面期望输出一致
    cout << r << endl;

    return 0;
}