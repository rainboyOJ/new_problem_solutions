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

struct WaitCmp {
    bool operator()(const Process &a, const Process &b) const {
        if (a.priority != b.priority) {
            return a.priority < b.priority;
        }
        if (a.arrive != b.arrive) {
            return a.arrive > b.arrive;
        }
        return a.id > b.id;
    }
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

    priority_queue<Process, vector<Process>, WaitCmp> pq;
    int n = (int) all.size();
    int idx = 0;
    ll now = 0;
    bool has_cur = false;
    Process cur;

    while (idx < n || has_cur || !pq.empty()) {
        if (!has_cur && pq.empty() && idx < n) {
            now = max(now, all[idx].arrive);
        }

        // 先把所有在当前时刻已经到达的进程加入等待队列。
        while (idx < n && all[idx].arrive <= now) {
            pq.push(all[idx]);
            idx++;
        }

        if (!has_cur) {
            if (pq.empty()) {
                continue;
            }
            cur = pq.top();
            pq.pop();
            has_cur = true;
        }

        ll next_arrive = (idx < n ? all[idx].arrive : (ll) 4e18);
        ll finish_time = now + cur.remain;

        if (finish_time <= next_arrive) {
            now = finish_time;
            cout << cur.id << ' ' << now << '\n';
            has_cur = false;
            continue;
        }

        // 先运行到下一个进程到达时刻。
        cur.remain -= (next_arrive - now);
        now = next_arrive;

        // 把这一时刻到达的所有进程加入等待队列。
        while (idx < n && all[idx].arrive == now) {
            pq.push(all[idx]);
            idx++;
        }

        if (!pq.empty() && pq.top().priority > cur.priority) {
            pq.push(cur);
            cur = pq.top();
            pq.pop();
        }
    }

    return 0;
}
