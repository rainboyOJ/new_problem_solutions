#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct PrefixSum {
    vector<ll> s;

    void init(const vector<ll> &a) {
        int n = static_cast<int>(a.size());
        s.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i) {
            s[i] = s[i - 1] + a[i - 1];
        }
    }

    ll query(int l, int r) const {
        return s[r] - s[l - 1];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<ll> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    PrefixSum ps;
    ps.init(a);

    ll ans = 0;
    for (int right = 1; right <= n; ++right) {
        // 右端点固定为 right 时，最多再向左并进来 k 个水壶。
        int left = max(1, right - k);
        ans = max(ans, ps.query(left, right));
    }

    cout << ans << '\n';
    return 0;
}
