/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-12 14:50
 * update_at: 2026-11-12 14:50
 */
#include <iostream>
#include <vector>

using namespace std;

const int maxn = 100000 + 50;
const int maxv = 1000000 + 5;
const int MOD = 1e9 + 7;

int a[maxn];
int dp[maxn];

// 全局静态 vector 数组：factors[x] 预先存储数值 x 的所有不超过 n 的因数
// 依照调和级数预处理，因数在压入时天然保持单调递增
vector<int> factors[maxv];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    int max_val = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] > max_val) max_val = a[i];
    }

    // 调和级数预处理：枚举因子 i <= n，将其分发给所有倍数 j = i, 2i, 3i, ...
    // 时间复杂度为 O(max_val * ln(n))，在 10^6 范围内运算量仅约 10^7，耗时约 0.05s
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= max_val; j += i) {
            factors[j].push_back(i);
        }
    }

    dp[0] = 1;

    for (int i = 1; i <= n; ++i) {
        int x = a[i];
        // 逆序遍历预处理好的因数列表，天然满足 0-1 背包从大到小逆序的要求
        // 运行期 0 次试除、0 次取模分解、0 次额外排序，常数极度优化
        for (auto it = factors[x].rbegin(); it != factors[x].rend(); ++it) {
            int d = *it;
            dp[d] = (dp[d] + dp[d - 1]) % MOD;
        }
    }

    int ans = 0;
    for (int len = 1; len <= n; ++len) {
        ans = (ans + dp[len]) % MOD;
    }

    cout << ans << "\n";
    return 0;
}
