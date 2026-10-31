/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 21:08
 * update_at: 2026-10-31 21:08
 */
// main2.cpp：排序后枚举区间，只适合 n <= 5000 的子任务。
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 5005;
ll a[MAXN]; // 排序后的原始数值

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    if (!(cin >> n >> m)) return 0;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }

    sort(a + 1, a + n + 1);

    ll ans = 1;
    // 枚举区间右端点作为目标值
    for (ll r = 1; r <= n; r++) {
        ll cost = 0;
        for (ll l = r; l >= 1; l--) {
            cost += a[r] - a[l]; // 新选一个数，补上它到目标值的差
            if (cost > m) break; // 再往左选，代价也不会减少
            ans = max(ans, r - l + 1);
        }
    }

    cout << ans << "\n";
    return 0;
}
