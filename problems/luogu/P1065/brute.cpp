#include <bits/stdc++.h>
using namespace std;

// brute.cpp：教学版暴力模拟。
// 每次枚举候选开始时间，并与该机器上已安排的所有区间逐个判冲突。
const int MAXM = 25;
const int MAXN = 25;

struct Interval {
    int l, r; // 占用 [l, r)
};

int m, n;
int order_list[MAXM * MAXN];
int machine_id[MAXN][MAXM];
int cost_time[MAXN][MAXM];
int next_step[MAXN];
int finish_time[MAXN];
vector<Interval> machine_jobs[MAXM];

bool overlap(int l1, int r1, int l2, int r2) {
    return max(l1, l2) < min(r1, r2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;
    int tot = m * n;

    for (int i = 1; i <= tot; i++) {
        cin >> order_list[i];
    }

    for (int job = 1; job <= n; job++) {
        for (int step = 1; step <= m; step++) {
            cin >> machine_id[job][step];
        }
    }

    for (int job = 1; job <= n; job++) {
        for (int step = 1; step <= m; step++) {
            cin >> cost_time[job][step];
        }
    }

    int answer = 0;

    for (int idx = 1; idx <= tot; idx++) {
        int job = order_list[idx];
        int step = ++next_step[job];
        int mac = machine_id[job][step];
        int len = cost_time[job][step];

        int start = finish_time[job];

        while (true) {
            bool ok = true;
            for (int i = 0; i < (int)machine_jobs[mac].size(); i++) {
                Interval seg = machine_jobs[mac][i];
                if (overlap(start, start + len, seg.l, seg.r)) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                break;
            }
            start++;
        }

        machine_jobs[mac].push_back({start, start + len});
        finish_time[job] = start + len;
        answer = max(answer, finish_time[job]);
    }

    cout << answer << '\n';
    return 0;
}
