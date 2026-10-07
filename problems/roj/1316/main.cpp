/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:11
 * update_at: 2026-10-05 09:11
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 1005; // n <= 1000，多开几个防止越界

ll f[MAXN]; // f[i]：从 i 出发能生成的不同数的个数（含 i 本身）

int main() {
    ll n;
    cin >> n;

    // f[0] = f[1] = 1：0 和 1 左边都补不了正整数，只能算自己
    f[0] = 1;
    f[1] = 1;
    // 差分后的递推：奇数不变，偶数多出 f[i/2]
    for (ll i = 2; i <= n; i++) {
        if (i % 2 == 0) {
            f[i] = f[i - 1] + f[i / 2];
        } else {
            f[i] = f[i - 1];
        }
    }

    cout << f[n] << endl;
    return 0;
}
