/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 22:15
 */
// brute.cpp：按定义先求平均值和方差，再逐项标准化。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<double> value(n);
    double average = 0;
    for (int i = 0; i < n; i++) {
        cin >> value[i];
        average += value[i];
    }
    average /= n;
    double variance = 0;
    for (int i = 0; i < n; i++) variance += (value[i] - average) * (value[i] - average);
    variance /= n;
    cout << setprecision(17);
    for (int i = 0; i < n; i++) cout << (value[i] - average) / sqrt(variance) << '\n';
    return 0;
}
