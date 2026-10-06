/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:14
 * update_at: 2026-10-06 16:14
 */
#include <iostream>
using namespace std;

typedef long long ll;

ll n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // 奇数必用到 2^0 = 1，而 1 不是 2 的正整数次幂，无解
    if (n & 1) {
        cout << -1 << "\n";
        return 0;
    }

    // 偶数的二进制展开中第 0 位为 0，其余置位 k>=1 对应的 2^k 即答案
    bool first = true;
    for (ll k = 62; k >= 1; k--) {
        if (n >> k & 1) {
            if (!first) cout << " ";
            first = false;
            cout << (1LL << k);
        }
    }
    cout << "\n";

    return 0;
}
