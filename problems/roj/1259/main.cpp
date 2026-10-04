/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:20
 * update_at: 2026-10-05 07:24
 */
#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;

const int MAXN = 205;

int n;
ll b[MAXN];      // 输入序列
int f[MAXN];     // f[i] 表示以 b[i] 结尾的最长不下降子序列长度

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> b[i];

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        f[i] = 1; // 至少包含自身
        for (int j = 1; j < i; ++j) {
            if (b[j] <= b[i] && f[j] + 1 > f[i]) {
                f[i] = f[j] + 1;
            }
        }
        if (f[i] > ans) ans = f[i];
    }

    // 本题归档答案只要求输出长度行
    cout << "max=" << ans << "\n";
    return 0;
}
