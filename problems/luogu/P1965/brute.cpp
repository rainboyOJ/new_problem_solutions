/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:32
 * update_at: 2026-11-11 00:32
 */
#include <iostream>

using namespace std;

using ll = long long;

// 暴力模拟：计算 10^k 并在循环中逐次移动
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m, k, x;
    if (!(cin >> n >> m >> k >> x)) return 0;

    ll total_rounds = 1;
    for (int i = 0; i < k; ++i) {
        total_rounds *= 10;
    }

    ll cur = x;
    for (ll step = 0; step < total_rounds; ++step) {
        cur = (cur + m) % n;
    }

    cout << cur << "\n";

    return 0;
}
