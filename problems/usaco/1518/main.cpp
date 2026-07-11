/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 18:13
 * update_at: 2026-07-11 18:17
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<ll> ans;

void solve_one_case() {
    ll m;
    int k;
    cin >> m >> k;

    ans.clear();
    ll base_sum = 0;

    // K 的第 i 位为 1，就放入一个 popcount 为 2^i 的最小数。
    for (int i = 0; i <= 4; i++) {
        if ((k & (1 << i)) != 0) {
            ll value = (1LL << (1 << i)) - 1;
            ans.push_back(value);
            base_sum += value;
        }
    }

    ll rest = m - base_sum;
    if (rest < 0) {
        cout << -1 << '\n';
        return;
    }

    if (rest == 1) {
        // 只有包含 1 时，才能把 1 改成 2，sum +1 且 popcount 不变。
        bool changed = false;
        for (int i = 0; i < (int)ans.size(); i++) {
            if (ans[i] == 1) {
                ans[i] = 2;
                changed = true;
                break;
            }
        }
        if (!changed) {
            cout << -1 << '\n';
            return;
        }
    } else if (rest >= 2) {
        if (rest % 2 == 0) {
            ans.push_back(rest / 2);
            ans.push_back(rest / 2);
        } else {
            ans.push_back(1);
            ans.push_back(2);
            ans.push_back((rest - 3) / 2);
            ans.push_back((rest - 3) / 2);
        }
    }

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << ans[i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve_one_case();
    }

    return 0;
}
