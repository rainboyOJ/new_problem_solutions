#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;

int n, k, p, r;
int answer_day[5005];
int need_count[5005], max_need_day[5005], target_question[5005];
vector<int> depend_rules[5005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> p;

    for (int i = 1; i <= n; ++i) {
        answer_day[i] = INF;
    }

    queue<int> q;
    for (int i = 1; i <= p; ++i) {
        int x;
        cin >> x;
        if (answer_day[x] > 0) {
            answer_day[x] = 0;
            q.push(x);
        }
    }

    cin >> r;
    for (int i = 1; i <= r; ++i) {
        int v, cnt;
        cin >> v >> cnt;
        target_question[i] = v;
        need_count[i] = cnt;
        max_need_day[i] = -1;

        for (int j = 1; j <= cnt; ++j) {
            int u;
            cin >> u;
            depend_rules[u].push_back(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int id : depend_rules[u]) {
            --need_count[id];
            max_need_day[id] = max(max_need_day[id], answer_day[u]);

            if (need_count[id] == 0) {
                int v = target_question[id];
                int cand = max_need_day[id] + 1;
                if (cand < answer_day[v]) {
                    answer_day[v] = cand;
                    q.push(v);
                }
            }
        }
    }

    if (answer_day[k] == INF) {
        cout << -1 << '\n';
    } else {
        cout << answer_day[k] << '\n';
    }

    return 0;
}
