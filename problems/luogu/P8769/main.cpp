#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

struct Choco {
    ll price;
    ll cnt;
    ll expire;
};

struct Node {
    ll price;
    ll cnt;

    bool operator < (const Node &other) const {
        return price > other.price;
    }
};

int x, n;
Choco a[MAXN];

bool cmp_expire_desc(const Choco &lhs, const Choco &rhs) {
    return lhs.expire > rhs.expire;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> x >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].price >> a[i].expire >> a[i].cnt;
    }

    sort(a + 1, a + n + 1, cmp_expire_desc);

    priority_queue<Node> pq;
    int ptr = 1;
    ll ans = 0;

    // 倒着考虑第 day 天要吃什么。
    // 这样 expiry >= day 的巧克力都可以用在这一天。
    for (int day = x; day >= 1; day--) {
        while (ptr <= n && a[ptr].expire >= day) {
            pq.push({a[ptr].price, a[ptr].cnt});
            ptr++;
        }

        while (!pq.empty() && pq.top().cnt == 0) {
            pq.pop();
        }

        if (pq.empty()) {
            cout << -1 << '\n';
            return 0;
        }

        Node cur = pq.top();
        pq.pop();
        ans += cur.price;
        cur.cnt--;
        if (cur.cnt > 0) {
            pq.push(cur);
        }
    }

    cout << ans << '\n';
    return 0;
}
