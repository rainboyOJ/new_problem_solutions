/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:18
 * update_at: 2026-10-05 08:18
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 1005;
ll f[MAXN];        // f[j] 表示恰好凑出 j 元的方案数
int price[4] = {10, 20, 50, 100};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;

    f[0] = 1;      // 凑出 0 元有一种空方案
    for (int i = 0; i < 4; i++) {
        for (int j = price[i]; j <= n; j++) {
            f[j] += f[j - price[i]];
        }
    }

    // 题目约定 n=0 时输出 0（空方案不计入）
    if (n == 0) cout << 0 << "\n";
    else cout << f[n] << "\n";
    return 0;
}
