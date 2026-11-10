/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:55
 * update_at: 2026-11-11 00:55
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 1e9;
const int MAXN = 105;
const int MAXM = 15;

int a[MAXN];
int prefix_sum[MAXN];

// 模 10 映射到 [0, 9]
inline int mod10(int val) {
    return ((val % 10) + 10) % 10;
}

// 获取子区间 [l, r] 的模 10 和
inline int get_seg(int l, int r) {
    return mod10(prefix_sum[r] - prefix_sum[l - 1]);
}

int dp_max[MAXN][MAXM];
int dp_min[MAXN][MAXM];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i + n] = a[i]; // 破环成链
    }

    for (int i = 1; i <= 2 * n; ++i) {
        prefix_sum[i] = prefix_sum[i - 1] + a[i];
    }

    int ans_min = INF;
    int ans_max = -1;

    // 枚举断点起始位置 s
    for (int s = 1; s <= n; ++s) {
        // 初始化单段 (j = 1) 的情况
        for (int i = 1; i <= n; ++i) {
            int w = get_seg(s, s + i - 1);
            dp_max[i][1] = w;
            dp_min[i][1] = w;
            for (int j = 2; j <= m; ++j) {
                dp_max[i][j] = -1;
                dp_min[i][j] = INF;
            }
        }

        // 递推划分段数 j
        for (int j = 2; j <= m; ++j) {
            for (int i = j; i <= n; ++i) {
                for (int p = j - 1; p < i; ++p) {
                    int w = get_seg(s + p, s + i - 1);
                    if (dp_max[p][j - 1] != -1) {
                        dp_max[i][j] = max(dp_max[i][j], dp_max[p][j - 1] * w);
                    }
                    if (dp_min[p][j - 1] != INF) {
                        dp_min[i][j] = min(dp_min[i][j], dp_min[p][j - 1] * w);
                    }
                }
            }
        }

        ans_min = min(ans_min, dp_min[n][m]);
        ans_max = max(ans_max, dp_max[n][m]);
    }

    cout << ans_min << "\n" << ans_max << "\n";

    return 0;
}
