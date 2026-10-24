/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 23:21
 * update_at: 2026-10-23 23:21
 */
#include <iostream>
#include <vector>
using namespace std;

// 节点数 <= 30，分数 <= 100，最大答案 <= 4e9，需要 long long
int n;
long long a[35];
long long dp[35][35];
int root[35][35];

// 递归打印前序遍历
void print_preorder(int l, int r) {
    if (l > r) return;
    int k = root[l][r];
    cout << k << " ";
    print_preorder(l, k - 1);
    print_preorder(k + 1, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    // 初始化：空子树加分为 1
    for (int i = 1; i <= n + 1; ++i) {
        for (int j = 0; j <= n + 1; ++j) {
            if (i > j) dp[i][j] = 1;
        }
    }

    // 单个节点的加分就是其自身权值，根为其自身
    for (int i = 1; i <= n; ++i) {
        dp[i][i] = a[i];
        root[i][i] = i;
    }

    // 区间 DP：len 从 2 到 n
    for (int len = 2; len <= n; ++len) {
        for (int l = 1; l + len - 1 <= n; ++l) {
            int r = l + len - 1;
            dp[l][r] = -1;
            for (int k = l; k <= r; ++k) {
                long long left_score = dp[l][k - 1];
                long long right_score = dp[k + 1][r];
                long long score = left_score * right_score + a[k];
                if (score > dp[l][r]) {
                    dp[l][r] = score;
                    root[l][r] = k;
                }
            }
        }
    }

    cout << dp[1][n] << "\n";
    print_preorder(1, n);
    cout << "\n";

    return 0;
}
