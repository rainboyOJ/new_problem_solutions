/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 10:20
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    double a;
    cin >> n >> a;
    int inside = 0;
    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        if (x * x + y * y <= a * a + 1e-12) inside++;
    }
    cout << fixed << setprecision(6) << 4.0 * inside / n << '\n';
    return 0;
}
