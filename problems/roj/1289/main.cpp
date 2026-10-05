/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:09
 * update_at: 2026-10-05 08:09
 */
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 25; // N 不超过 15

ll h[MAXN]; // 导弹高度
ll f[MAXN]; // f[i] 表示以 h[i] 结尾的最长不增子序列长度

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &h[i]);
    }

    ll ans = 0;
    for (int i = 1; i <= n; ++i) {
        f[i] = 1; // 至少拦截自己这一发
        // 枚举前面的导弹 j，若 h[j] 不低于 h[i] 则可接上
        for (int j = 1; j < i; ++j) {
            if (h[j] >= h[i]) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
        if (f[i] > ans) {
            ans = f[i];
        }
    }

    printf("%lld\n", ans);
    return 0;
}
