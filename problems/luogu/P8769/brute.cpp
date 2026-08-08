#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = (1LL << 60);

int x, n;
ll price_[15], expire_[15];
int cnt_[15];
map<vector<int>, ll> memo;

// day 表示当前要给第 day 天选巧克力。
ll dfs(int day, vector<int> cnt) {
    if (day == 0) {
        return 0;
    }

    vector<int> key;
    key.push_back(day);
    for (int v : cnt) {
        key.push_back(v);
    }
    map<vector<int>, ll>::iterator it = memo.find(key);
    if (it != memo.end()) {
        return it->second;
    }

    ll ans = INF;
    for (int i = 0; i < n; i++) {
        if (cnt[i] == 0) {
            continue;
        }
        if (expire_[i] < day) {
            continue;
        }
        cnt[i]--;
        ll sub = dfs(day - 1, cnt);
        cnt[i]++;
        if (sub != INF) {
            ans = min(ans, sub + price_[i]);
        }
    }

    memo[key] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> x >> n;
    for (int i = 0; i < n; i++) {
        cin >> price_[i] >> expire_[i] >> cnt_[i];
    }

    vector<int> cnt(cnt_, cnt_ + n);
    memo.clear();
    ll ans = dfs(x, cnt);
    if (ans == INF) {
        cout << -1 << '\n';
    }
    else {
        cout << ans << '\n';
    }
    return 0;
}
