/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-12 14:24
 * update_at: 2026-11-12 14:24
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 100000 + 50;
const int MOD = 1e9 + 7;

int a[maxn];
// dp[k] 表示当前为止，长度为 k 的优秀子序列的总方案数
int dp[maxn];

// 存储当前元素的所有因子（由于 10^6 以内因数最多 240 个，开 300 足够）
int divs[300];
int div_cnt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    // 初始状态：空序列方案数为 1
    dp[0] = 1;

    for (int i = 1; i <= n; ++i) {
        int x = a[i];
        div_cnt = 0;

        // 1. 在 O(sqrt(x)) 时间内找出 x 的所有因子，且因子不超过当前最大可能长度 n
        for (int d = 1; d * d <= x; ++d) {
            if (x % d == 0) {
                if (d <= n) divs[div_cnt++] = d;
                if (d * d != x && x / d <= n) {
                    divs[div_cnt++] = x / d;
                }
            }
        }

        // 2. 将因子按从大到小（降序）排序，类似于 0-1 背包逆序遍历，防止当前数字被重复使用
        sort(divs, divs + div_cnt, greater<int>());

        // 3. 状态转移：x 作为优秀子序列的第 d 个元素，前面需要拼接长度为 d - 1 的优秀子序列
        for (int k = 0; k < div_cnt; ++k) {
            int d = divs[k];
            dp[d] = (dp[d] + dp[d - 1]) % MOD;
        }
    }

    // 统计所有长度非空的优秀子序列方案总数
    int ans = 0;
    for (int len = 1; len <= n; ++len) {
        ans = (ans + dp[len]) % MOD;
    }

    cout << ans << "\n";
    return 0;
}
