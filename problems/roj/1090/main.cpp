/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:39
 * update_at: 2026-10-05 00:39
 */
#include <iostream>
using namespace std;

typedef long long ll;

int main() {
    ll m, k;
    cin >> m >> k;

    // 逐位取个位统计数字 3 出现的次数（m 最多五位数）
    ll count_of_3 = 0;
    ll t = m;
    while (t > 0) {
        if (t % 10 == 3) {
            count_of_3++;
        }
        t /= 10;
    }

    // 两个条件必须同时满足：能被 19 整除，且 3 恰好出现 k 次
    if (m % 19 == 0 && count_of_3 == k) {
        cout << "YES" << "\n";
    } else {
        cout << "NO" << "\n";
    }

    return 0;
}
