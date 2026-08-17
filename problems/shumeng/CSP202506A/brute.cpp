/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:53
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    while (k--) {
        int mu, sigma, n;
        cin >> mu >> sigma >> n;

        // 朴素做法：直接用浮点数算 (n-mu)/sigma 的百分位，
        // 由于浮点误差需要加小量再取整，不如主解的整数精确计算
        double z = (double)(n - mu) / sigma;
        int hundredths = (int)(z * 100 + 1e-9);
        cout << hundredths / 10 + 1 << ' ' << hundredths % 10 + 1 << '\n';
    }
    return 0;
}
