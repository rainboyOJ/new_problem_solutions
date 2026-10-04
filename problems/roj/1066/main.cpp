/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:57
 * update_at: 2026-10-04 23:57
 */

#include <iostream>
using namespace std;

typedef long long ll;

ll m, n;
ll first_term, last_term; // 区间 [m, n] 内 17 的第一个倍数、最后一个倍数
ll term_count;            // 等差数列的项数

int main() {
    cin >> m >> n;

    // 首项：>= m 的最小 17 的倍数
    if (m % 17 == 0) {
        first_term = m;
    } else {
        first_term = m + (17 - m % 17);
    }
    // 末项：<= n 的最大 17 的倍数
    last_term = n - n % 17;

    if (first_term > last_term) { // 区间内没有 17 的倍数
        cout << 0 << endl;
        return 0;
    }

    // 符合条件的数构成公差为 17 的等差数列，首末项平均后乘项数
    term_count = (last_term - first_term) / 17 + 1;
    cout << (first_term + last_term) * term_count / 2 << endl;

    return 0;
}
