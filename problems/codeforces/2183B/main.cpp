/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-15 08:45
 * update_at: 2026-07-15 09:15
 */
#include <bits/stdc++.h>
using namespace std;

int T;
int n, k;
int a[200005];
bool present[200005]; // present[v] = v 是否在数组中出现

void solve() {
    cin >> n >> k;
    for (int i = 0; i <= n; i++) present[i] = false;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] <= n) present[a[i]] = true;
    }
    // 统计 {0, 1, ..., k-2} 中在数组里连续出现的值的个数
    int ans = 0;
    for (int v = 0; v < k - 1; v++) {
        if (present[v]) ans++;
        else break;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> T;
    while (T--) solve();
    return 0;
}
