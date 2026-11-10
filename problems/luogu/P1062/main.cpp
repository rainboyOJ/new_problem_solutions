/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:16
 * update_at: 2026-11-11 00:16
 */
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long k;
    int n;
    if (!(cin >> k >> n)) return 0;

    long long ans = 0;
    long long base = 1;

    // 将 n 的二进制位依次解释为 k 进制的各个权重位
    while (n > 0) {
        if (n & 1) {
            ans += base;
        }
        base *= k;
        n >>= 1;
    }

    cout << ans << "\n";

    return 0;
}
