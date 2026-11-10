/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 22:50
 * update_at: 2026-11-10 22:50
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

using int128 = __int128;

const int MAXM = 85;

// a 存储当前行的数字
int a[MAXM];

// pow2[k] 存储 2^k
int128 pow2[MAXM];

// dp[L][R] 表示当前行剩余区间为 [L, R] 时，后续取数能获得的最大得分
int128 dp[MAXM][MAXM];

// 打印 __int128 的输出函数
void print_int128(int128 x) {
    if (x == 0) {
        cout << 0;
        return;
    }
    string s;
    while (x > 0) {
        s.push_back('0' + (x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

// 求解单行的最大得分
int128 solve_row(int m) {
    // 按剩余区间长度从 1 到 m 递推
    for (int len = 1; len <= m; ++len) {
        // 当前是在进行第 k 次取数（共取走 m - len 个数）
        int k = m - len + 1;

        for (int L = 1; L + len - 1 <= m; ++L) {
            int R = L + len - 1;
            if (len == 1) {
                // 仅剩一个元素时（第 m 次取数）
                dp[L][R] = static_cast<int128>(a[L]) * pow2[m];
            } else {
                // 两种决策：本次取行首 a[L]，或者本次取行尾 a[R]
                int128 pick_left = dp[L + 1][R] + static_cast<int128>(a[L]) * pow2[k];
                int128 pick_right = dp[L][R - 1] + static_cast<int128>(a[R]) * pow2[k];
                dp[L][R] = max(pick_left, pick_right);
            }
        }
    }
    return dp[1][m];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    // 预处理 2 的各次幂
    pow2[0] = 1;
    for (int i = 1; i <= m; ++i) {
        pow2[i] = pow2[i - 1] * 2;
    }

    int128 total_score = 0;

    // 独立处理每一行
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[j];
        }
        total_score += solve_row(m);
    }

    print_int128(total_score);
    cout << "\n";

    return 0;
}
