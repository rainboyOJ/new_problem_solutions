/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:18
 * update_at: 2026-10-05 08:18
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXM = 12880 + 5; // 背包容量上限 + 1

ll n, m;
ll f[MAXM]; // f[v]：重量不超过 v 时能获得的最大价值

void solve() {
    cin >> n >> m;
    for (ll i = 1; i <= n; i++) {
        ll w, c;
        cin >> w >> c;
        // 倒序枚举容量，保证每件物品至多选一次
        for (ll v = m; v >= w; v--) {
            if (f[v] < f[v - w] + c) {
                f[v] = f[v - w] + c;
            }
        }
    }
    cout << f[m] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
