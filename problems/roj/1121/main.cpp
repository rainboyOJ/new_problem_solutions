/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:31
 * update_at: 2026-10-05 02:31
 */

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 105;
int a[MAXN][MAXN]; // a[i][j] 表示第 i 行第 j 列的元素（1 起编号）

int m, n;

// 思路：边缘 = 全部 − 内部。直接读入时累加所有元素，再单独把
// 内部子矩阵（第 2..m-1 行、第 2..n-1 列）累加一次，相减即得。
// m ≤ 2 或 n ≤ 2 时内部区域为空，自然退化为整矩阵求和。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    if (!(cin >> m >> n)) return 0;
    ll total = 0, inner = 0;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> a[i][j];
            total += a[i][j];
            // 内部行 i∈[2,m-1] 且内部列 j∈[2,n-1]
            if (i >= 2 && i <= m - 1 && j >= 2 && j <= n - 1)
                inner += a[i][j];
        }
    }
    cout << total - inner << "\n";
    return 0;
}
