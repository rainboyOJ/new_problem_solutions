/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:53
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;
    while (k--) {
        long long mu, sigma, n;
        cin >> mu >> sigma >> n;

        // 标准化的查表值 (n-mu)/sigma，放大 100 倍化为整数。
        // 因为 sigma 是 100 的因子，这里可精确整除，避免浮点误差。
        long long hundredths = (n - mu) * 100 / sigma;

        // 十分位决定行号，百分位决定列号，下标均从 1 开始
        cout << hundredths / 10 + 1 << ' ' << hundredths % 10 + 1 << '\n';
    }
    return 0;
}
