#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll ans = 0;

void dfs(const vector<ll> &cards, ll score) {
    ans = max(ans, score);

    int n = static_cast<int>(cards.size());
    for (int len = 2; len <= n; ++len) {
        ll sum = 0;
        for (int i = 0; i < len; ++i) {
            sum += cards[i];
        }

        vector<ll> next_cards;
        next_cards.push_back(sum);
        for (int i = len; i < n; ++i) {
            next_cards.push_back(cards[i]);
        }

        dfs(next_cards, score + sum);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> cards(n);
    for (int i = 0; i < n; ++i) {
        cin >> cards[i];
    }

    dfs(cards, 0);
    cout << ans << '\n';
    return 0;
}
