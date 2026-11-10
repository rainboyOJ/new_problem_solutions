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

using namespace std;

// 暴力版本：DFS 搜索较小面额能否组合出当前目标数
int n;
int a[105];

bool dfs_can_form(int idx, int rest) {
    if (rest == 0) return true;
    if (idx < 1) return false;
    for (int count = 0; count * a[idx] <= rest; ++count) {
        if (dfs_can_form(idx - 1, rest - count * a[idx])) {
            return true;
        }
    }
    return false;
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    sort(a + 1, a + n + 1);

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        if (!dfs_can_form(i - 1, a[i])) {
            ans++;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) return 0;
    while (t--) solve();
    return 0;
}
