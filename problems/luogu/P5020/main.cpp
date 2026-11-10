/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:47
 * update_at: 2026-11-11 00:47
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MAXV = 25005;

int n;
int a[105];
bool f[MAXV];

void solve() {
    cin >> n;
    int max_val = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        max_val = max(max_val, a[i]);
    }

    sort(a + 1, a + n + 1);

    memset(f, 0, sizeof(bool) * (max_val + 5));
    f[0] = true;

    int ans = 0;

    for (int i = 1; i <= n; ++i) {
        // 如果当前面额不能被已有的更小面额拼出，则必须保留
        if (!f[a[i]]) {
            ans++;
            // 用该面额进行完全背包更新
            for (int v = a[i]; v <= max_val; ++v) {
                if (f[v - a[i]]) {
                    f[v] = true;
                }
            }
        }
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;

    while (t--) {
        solve();
    }

    return 0;
}
