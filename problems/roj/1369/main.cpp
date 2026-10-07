/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:13
 * update_at: 2026-10-05 12:13
 */

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 30005;

ll a[MAXN]; // 每堆果子的重量

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    // 小根堆：每次取最小的两堆合并
    priority_queue<ll, vector<ll>, greater<ll> > q;
    for (int i = 1; i <= n; ++i) q.push(a[i]);

    ll ans = 0;
    while (q.size() > 1) {
        ll x = q.top(); q.pop();
        ll y = q.top(); q.pop();
        ll s = x + y;   // 合并新堆的重量
        ans += s;       // 本次耗费体力
        q.push(s);
    }

    cout << ans << "\n";
    return 0;
}
