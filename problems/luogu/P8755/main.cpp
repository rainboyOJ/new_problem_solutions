#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200005;

struct Node {
    ll end_time;
    ll cost;

    bool operator < (const Node &other) const {
        return end_time > other.end_time;
    }
};

int n, m;
ll cap[MAXN];
ll used[MAXN];
priority_queue<Node> pq[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> cap[i];
    }

    for (int i = 1; i <= m; i++) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;

        // 先释放掉这台机器上所有已经结束的任务。
        while (!pq[b].empty() && pq[b].top().end_time <= a) {
            used[b] -= pq[b].top().cost;
            pq[b].pop();
        }

        if (cap[b] - used[b] < d) {
            cout << -1 << '\n';
            continue;
        }

        used[b] += d;
        pq[b].push({a + c, d});
        cout << cap[b] - used[b] << '\n';
    }

    return 0;
}
