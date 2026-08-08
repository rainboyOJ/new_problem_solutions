#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll INF = (1LL << 60);

map<vector<ll>, ll> memo;

ll dfs(vector<ll> a) {
    if (a.size() == 1) {
        return 0;
    }
    sort(a.begin(), a.end());

    map<vector<ll>, ll>::iterator it = memo.find(a);
    if (it != memo.end()) {
        return it->second;
    }

    ll ans = INF;
    int n = (int) a.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            vector<ll> nxt;
            for (int k = 0; k < n; k++) {
                if (k == i || k == j) {
                    continue;
                }
                nxt.push_back(a[k]);
            }
            nxt.push_back(a[i] + a[j]);
            ans = min(ans, dfs(nxt) + a[i] + a[j]);
        }
    }

    memo[a] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    memo.clear();
    cout << dfs(a) << '\n';
    return 0;
}
