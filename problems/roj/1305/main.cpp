/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2025-07-16 12:00
 * update_at: 2026-10-05 08:49
 */
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 50005;

ll a[MAXN];     // 原序列
ll f[MAXN];     // f[i]：右端点恰为 i 的最大子段和
ll g[MAXN];     // g[i]：a[1..i] 中的最大子段和（f 的前缀最大值）
ll h[MAXN];     // h[i]：左端点恰为 i 的最大子段和

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; ++i) cin >> a[i];

        // 正向：f[i] = max(a[i], f[i-1] + a[i])；g[i] = max(g[i-1], f[i])
        f[1] = a[1];
        g[1] = a[1];
        for (int i = 2; i <= n; ++i) {
            f[i] = max(a[i], f[i - 1] + a[i]);
            g[i] = max(g[i - 1], f[i]);
        }

        // 反向：h[i] = max(a[i], h[i+1] + a[i])
        h[n] = a[n];
        for (int i = n - 1; i >= 1; --i) {
            h[i] = max(a[i], h[i + 1] + a[i]);
        }

        // 枚举分界 k：左段在 [1,k]，右段从 k+1 开始
        ll ans = a[1] + a[2];
        for (int k = 1; k < n; ++k) {
            ans = max(ans, g[k] + h[k + 1]);
        }

        cout << ans << '\n';
    }
    return 0;
}
