/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 19:35
 * update_at: 2026-07-11 19:38
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Item {
    ll x;
    ll t;
    int is_cow; // 1 表示 Nhoj 的牛，0 表示草地
};

int k, m, n;
vector<Item> a;
vector<ll> gain;

bool cmp_item(Item p, Item q) {
    return p.x < q.x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> k >> m >> n;
    for (int i = 1; i <= k; i++) {
        ll p, t;
        cin >> p >> t;
        a.push_back((Item){p, t, 0});
    }
    for (int i = 1; i <= m; i++) {
        ll f;
        cin >> f;
        a.push_back((Item){f, 0, 1});
    }

    sort(a.begin(), a.end(), cmp_item);

    int last_cow = -1;
    ll segment_sum = 0;

    for (int i = 0; i < (int)a.size(); i++) {
        if (a[i].is_cow == 0) {
            segment_sum += a[i].t;
            continue;
        }

        if (last_cow == -1) {
            // 最左边没有 Nhoj 的牛，一头 John 的牛可以全拿。
            gain.push_back(segment_sum);
        } else {
            ll best_one = 0;
            ll cur_sum = 0;
            int r = last_cow;
            ll width = a[i].x - a[last_cow].x;

            // 中间区间：一头牛能覆盖一个长度小于 width/2 的窗口。
            for (int l = last_cow + 1; l < i; l++) {
                while (r + 1 < i && (a[r + 1].x - a[l].x) * 2 < width) {
                    r++;
                    cur_sum += a[r].t;
                }
                if (best_one < cur_sum) {
                    best_one = cur_sum;
                }
                cur_sum -= a[l].t;
            }

            gain.push_back(best_one);
            gain.push_back(segment_sum - best_one);
        }

        last_cow = i;
        segment_sum = 0;
    }

    // 最右边没有 Nhoj 的牛，也可以用一头牛全拿。
    gain.push_back(segment_sum);

    sort(gain.begin(), gain.end(), greater<ll>());

    ll ans = 0;
    for (int i = 0; i < n && i < (int)gain.size(); i++) {
        ans += gain[i];
    }

    cout << ans << '\n';

    return 0;
}
