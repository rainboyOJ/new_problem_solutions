/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:05
 * update_at: 2026-10-04 22:06
 */
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

ll n, x;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 多组数据读到 EOF
    while (cin >> n) {
        // 唯一需要关心的是：是否只剩一堆且该堆为偶数
        if (n != 1) {
            // n >= 2 时 Alice 必败：Bob 总能在任意非空堆拿 1 颗续命
            for (ll i = 1; i <= n; ++i) cin >> x;
            cout << "NO\n";
        } else {
            cin >> x;
            cout << (x % 2 == 0 ? "YES" : "NO") << "\n";
        }
    }
    return 0;
}
