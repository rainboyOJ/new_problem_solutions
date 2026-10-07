/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:46
 * update_at: 2026-10-06 09:46
 */
// roj 2047 usaco-3.2.2 二进制数01串
// 数位计数 + 字典序逐位试填：先算出当前位填 0 的分支规模，再决定这一位填 0 还是填 1。

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 40;

ll f[MAXN][MAXN]; // f[i][j] 表示长度为 i 且其中 1 的个数不超过 j 的二进制串总数

int main() {
    ll n, l, rank_id;
    cin >> n >> l >> rank_id;

    // 边界：空串算一种方案；没有 1 的配额时剩余位只能全填 0
    for (int j = 0; j <= l; j++) {
        f[0][j] = 1;
    }
    for (int i = 0; i <= n; i++) {
        f[i][0] = 1;
    }

    // f[i][j] = 最高位填 0 的方案数 + 最高位填 1 的方案数
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= l; j++) {
            f[i][j] = f[i - 1][j] + f[i - 1][j - 1];
        }
    }

    // 自高向低逐位试填：branch_zero 是当前位填 0 时后续子树的合法串数量
    ll left_ones = l;
    for (int i = n; i >= 1; i--) {
        ll branch_zero = f[i - 1][left_ones];
        if (rank_id <= branch_zero) {
            cout << '0';
        } else {
            cout << '1';
            rank_id -= branch_zero;
            left_ones--;
        }
    }
    cout << '\n';

    return 0;
}
