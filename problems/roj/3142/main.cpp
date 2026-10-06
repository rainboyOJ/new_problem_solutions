/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 22:20
 * update_at: 2026-10-06 11:59
 */
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 4005;           // N 最大 4000
const unsigned int MOD = 1u << 31; // 模数 2147483648 = 2^31

unsigned int f[MAXN];            // f[j] 表示凑出和 j 的方案数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    f[0] = 1;                      // 和为 0 只有空选一种方案
    for (int i = 1; i <= n; ++i) {   // 依次允许使用加数 i
        for (int j = i; j <= n; ++j) {
            // 完全背包：正序更新，f[j-i] 已包含可再用 i 的信息
            f[j] = (f[j] + f[j - i]) & (MOD - 1);
        }
    }

    // 减去不退化的单加数方案 N = N
    unsigned int ans = (f[n] + MOD - 1) & (MOD - 1);
    cout << ans << "\n";
    return 0;
}
