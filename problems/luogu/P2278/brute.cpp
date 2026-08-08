#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Process {
    ll id;
    ll arrive;
    ll run;
    ll priority;
    ll remain;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Process> all;
    while (true) {
        Process p;
        if (!(cin >> p.id >> p.arrive >> p.run >> p.priority)) {
            break;
        }
        p.remain = p.run;
        all.push_back(p);
    }

    int n = (int) all.size();
    vector<int> alive(n, 1);
    vector<int> started(n, 0);
    ll now = 0;
    int finished = 0;

    auto pick_best = [&](ll t) -> int {
        int best = -1;
        for (int i = 0; i < n; i++) {
            if (!alive[i]) {
                continue;
            }
            if (all[i].arrive > t) {
                continue;
            }
            if (best == -1 ||
                all[i].priority > all[best].priority ||
                (all[i].priority == all[best].priority && all[i].arrive < all[best].arrive) ||
                (all[i].priority == all[best].priority && all[i].arrive == all[best].arrive && all[i].id < all[best].id)) {
                best = i;
            }
        }
        return best;
    };

    while (finished < n) {
        int cur = pick_best(now);
        if (cur == -1) {
            ll nxt = (ll) 4e18;
            for (int i = 0; i < n; i++) {
                if (alive[i]) {
                    nxt = min(nxt, all[i].arrive);
                }
            }
            now = nxt;
            continue;
        }

        ll nxt = now + all[cur].remain;
        for (int i = 0; i < n; i++) {
            if (!alive[i] || i == cur) {
                continue;
            }
            if (all[i].arrive > now && all[i].arrive < nxt && all[i].priority > all[cur].priority) {
                nxt = min(nxt, all[i].arrive);
            }
        }

        all[cur].remain -= (nxt - now);
        now = nxt;

        if (all[cur].remain == 0) {
            cout << all[cur].id << ' ' << now << '\n';
            alive[cur] = 0;
            finished++;
        }
    }

    return 0;
}
