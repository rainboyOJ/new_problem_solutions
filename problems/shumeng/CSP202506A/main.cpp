/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 09:45
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
        long long hundredths = (n - mu) * 100 / sigma;
        cout << hundredths / 10 + 1 << ' ' << hundredths % 10 + 1 << '\n';
    }
    return 0;
}
