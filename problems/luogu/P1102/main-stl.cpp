/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 01:16
 * update_at: 2026-10-07 01:17
 */
/* P1102 A-B 数对 */
/* STL 写法：用 map<ll, ll> 统计每个数出现的次数，再对每个键 x 累加 cnt[x] * cnt[x + C]。 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n, c;
map<ll, ll> cnt; // cnt[x] 表示数值 x 在原序列中出现的次数；数值可能很大，键用 ll

void read_input() {
    cin >> n >> c;
    for (ll i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        // 键 x 不存在时 operator[] 先插入默认值 0，再自增，正好完成一次计数。
        cnt[x]++;
    }
}

void solve() {
    ll ans = 0; // 位置数对数量最多到 n^2 量级，用 ll 累加

    // 按键升序遍历每一种出现过的数值，把它当作较小的那个数 B，去查 A = B + C 的计数。
    for (map<ll, ll>::iterator it = cnt.begin(); it != cnt.end(); it++) {
        ll value_b = it->first;
        ll count_b = it->second;

        // 这里必须用 find：operator[] 会把不存在的键插入 map，
        // 边遍历边插入会让后面不断冒出新的键，循环失控。
        map<ll, ll>::iterator it_a = cnt.find(value_b + c);
        if (it_a != cnt.end()) {
            // B 的每个位置和 A 的每个位置都能配对，所以两边计数相乘。
            ans += count_b * it_a->second;
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
