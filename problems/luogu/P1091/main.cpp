/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-10 22:57
 * update_at: 2026-11-10 22:57
 */
#include <algorithm>
#include <iostream>

using namespace std;

const int MAXN = 105;

int t[MAXN];
int f[MAXN]; // f[i]: 以 t[i] 结尾的最长上升子序列长度
int g[MAXN]; // g[i]: 以 t[i] 开头的最长下降子序列长度

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    for (int i = 1; i <= n; ++i) {
        cin >> t[i];
    }

    // 正向 DP：求以 t[i] 结尾的最长上升子序列
    for (int i = 1; i <= n; ++i) {
        f[i] = 1;
        for (int j = 1; j < i; ++j) {
            if (t[j] < t[i]) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
    }

    // 反向 DP：求以 t[i] 开头的最长下降子序列
    for (int i = n; i >= 1; --i) {
        g[i] = 1;
        for (int j = n; j > i; --j) {
            if (t[j] < t[i]) {
                g[i] = max(g[i], g[j] + 1);
            }
        }
    }

    // 枚举合唱队形的中心峰顶位置 i，寻找最大保留人数
    int max_keep = 0;
    for (int i = 1; i <= n; ++i) {
        max_keep = max(max_keep, f[i] + g[i] - 1);
    }

    // 最少出列人数 = 总人数 - 最多保留人数
    cout << n - max_keep << "\n";

    return 0;
}
