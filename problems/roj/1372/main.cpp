/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 12:23
 * update_at: 2026-10-05 12:23
 */

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll n, m, x;
multiset<ll> s; // 未支付账单的多重集合

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> m;
        for (ll j = 1; j <= m; j++) {
            cin >> x;
            s.insert(x);
        }
        // 取出并删除最小和最大两张（不同账单，面额可相同）
        multiset<ll>::iterator it_min = s.begin();
        multiset<ll>::iterator it_max = prev(s.end());
        ll low = *it_min;
        ll high = *it_max;
        cout << low << " " << high << "\n";
        s.erase(it_min);
        // 若最小和最大指向同一元素，删除后再取最大会失效，需重新定位
        if (it_max == it_min) {
            it_max = prev(s.end());
        }
        s.erase(it_max);
    }
    return 0;
}
