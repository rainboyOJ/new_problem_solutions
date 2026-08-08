#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Task {
    ll end_time;
    ll cost;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<ll> cap(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> cap[i];
    }

    vector<vector<Task> > tasks(n + 1);
    vector<ll> used(n + 1, 0);

    for (int i = 1; i <= m; i++) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;

        vector<Task> alive;
        used[b] = 0;
        for (Task t : tasks[b]) {
            if (t.end_time > a) {
                alive.push_back(t);
                used[b] += t.cost;
            }
        }
        tasks[b].swap(alive);

        if (cap[b] - used[b] < d) {
            cout << -1 << '\n';
            continue;
        }

        tasks[b].push_back({a + c, d});
        used[b] += d;
        cout << cap[b] - used[b] << '\n';
    }

    return 0;
}
