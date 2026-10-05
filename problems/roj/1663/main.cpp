/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 01:38
 * update_at: 2026-10-06 01:38
 */

#include <iostream>

using namespace std;

typedef long long ll;

int main() {
    ll n; // 石子总数
    ll k; // 每步最多取走的石子数
    cin >> n >> k;

    // 巴什博弈：N 是 K+1 的倍数时先手必败，否则先手必胜
    if (n % (k + 1) != 0) {
        cout << 1 << endl;
    } else {
        cout << 2 << endl;
    }

    return 0;
}
