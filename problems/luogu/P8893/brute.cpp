#include <bits/stdc++.h>
using namespace std;

struct Rule {
    int v;
    int need_mask;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, p;
    cin >> n >> k >> p;

    int init_mask = 0;
    for (int i = 1; i <= p; ++i) {
        int x;
        cin >> x;
        init_mask |= 1 << (x - 1);
    }

    int r;
    cin >> r;
    vector<Rule> rules(r);
    for (int i = 0; i < r; ++i) {
        int v, cnt;
        cin >> v >> cnt;
        rules[i].v = v;
        rules[i].need_mask = 0;
        for (int j = 0; j < cnt; ++j) {
            int u;
            cin >> u;
            rules[i].need_mask |= 1 << (u - 1);
        }
    }

    queue<pair<int, int>> q;
    map<pair<int, int>, int> dist;
    q.push({0, init_mask});
    dist[{0, init_mask}] = 0;

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        int solved = cur.first;
        int rec = cur.second;
        int day = dist[cur];

        int available = rec & (~solved);
        for (int take = available;; take = (take - 1) & available) {
            int new_solved = solved | take;
            if (new_solved & (1 << (k - 1))) {
                cout << day << '\n';
                return 0;
            }

            int new_rec = rec;
            for (const auto &rule : rules) {
                if ((new_solved & rule.need_mask) == rule.need_mask &&
                    (take & rule.need_mask) != 0) {
                    new_rec |= 1 << (rule.v - 1);
                }
            }

            pair<int, int> nxt = {new_solved, new_rec};
            if (!dist.count(nxt)) {
                dist[nxt] = day + 1;
                q.push(nxt);
            }

            if (take == 0) {
                break;
            }
        }
    }

    cout << -1 << '\n';
    return 0;
}
