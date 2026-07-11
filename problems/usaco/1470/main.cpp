/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 18:26
 * update_at: 2026-07-11 18:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 500005;

int n;
int a[MAXN], b[MAXN];
vector<pair<int, int> > occ[MAXN];

ll ways2(ll x) {
    return x * (x + 1) / 2;
}

ll calc_one_direction() {
    for (int v = 1; v <= n; v++) {
        occ[v].clear();
    }

    for (int i = 0; i < n; i++) {
        occ[b[i]].push_back(make_pair(i, 1)); // 1 表示 b 中的位置
        occ[a[i]].push_back(make_pair(i, 0)); // 0 表示 a 中的位置
    }

    ll res = 0;

    for (int value = 1; value <= n; value++) {
        vector<int> small_stack;
        int big_count = 0;
        ll small_sum = 0;

        // 从右往左处理同一种品种的出现位置。
        for (int k = (int)occ[value].size() - 1; k >= 0; k--) {
            int idx = occ[value][k].first;
            int type = occ[value][k].second;

            if (type == 1) {
                int dist_right = n - idx;
                small_stack.push_back(dist_right);
                small_sum += dist_right;
            } else {
                int left_choices = idx + 1;
                while (!small_stack.empty() && small_stack.back() > left_choices) {
                    small_sum -= small_stack.back();
                    small_stack.pop_back();
                    big_count++;
                }
                res += small_sum + 1LL * big_count * left_choices;
            }
        }
    }

    return res;
}

void solve() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    ll ans = 0;

    // i == j 的贡献：反转区间不包含 i，或者包含 i 且 i 仍在中心。
    for (int i = 0; i < n; i++) {
        if (a[i] == b[i]) {
            ans += ways2(i) + ways2(n - 1 - i) + min(i, n - 1 - i) + 1;
        }
    }

    ans += calc_one_direction();

    reverse(a, a + n);
    reverse(b, b + n);
    ans += calc_one_direction();

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
