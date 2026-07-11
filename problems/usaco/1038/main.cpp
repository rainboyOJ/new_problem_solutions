/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 20:22
 * update_at: 2026-07-11 20:23
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXM = 100005;

int n, m;
pair<ll, ll> seg[MAXM];

bool check(ll dist) {
    ll cnt = 0;
    ll last = 0;

    for (int i = 1; i <= m; i++) {
        ll pos;
        if (cnt == 0) {
            pos = seg[i].first;
        } else {
            pos = max(last + dist, seg[i].first);
        }

        if (pos <= seg[i].second) {
            ll add = (seg[i].second - pos) / dist + 1;
            cnt += add;
            last = pos + (add - 1) * dist;
            if (cnt >= n) return true;
        }
    }

    return cnt >= n;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> seg[i].first >> seg[i].second;
    }

    sort(seg + 1, seg + m + 1);

    ll left = 1;
    ll right = seg[m].second - seg[1].first;
    ll ans = 1;

    while (left <= right) {
        ll mid = (left + right) / 2;
        if (check(mid)) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    cout << ans << '\n';
    return 0;
}
