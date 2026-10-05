/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:03
 * update_at: 2026-10-05 08:03
 */

#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 1005; // 序列最大长度

ll a[MAXN];   // 输入序列
ll f[MAXN];   // f[i] 表示以 a[i] 结尾的最大上升子序列和

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        f[i] = a[i]; // 至少选 a[i] 一个元素
        for (int j = 1; j < i; j++) {
            if (a[j] < a[i]) { // 严格递增才能接上
                f[i] = max(f[i], f[j] + a[i]);
            }
        }
        ans = max(ans, f[i]);
    }

    cout << ans << "\n";
    return 0;
}
