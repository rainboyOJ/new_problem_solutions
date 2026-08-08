#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    priority_queue<ll, vector<ll>, greater<ll> > pq;
    for (int i = 1; i <= n; i++) {
        ll x;
        cin >> x;
        pq.push(x);
    }

    ll ans = 0;
    while (pq.size() > 1) {
        ll a = pq.top();
        pq.pop();
        ll b = pq.top();
        pq.pop();

        ll sum = a + b;
        ans += sum;
        pq.push(sum);
    }

    cout << ans << '\n';
    return 0;
}
