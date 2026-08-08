#include <bits/stdc++.h>
using namespace std;

struct Job {
    int t;
    int s;
};

int n;
Job job[10];
bool used[10];

bool dfs(int done, int now) {
    if (done == n) return true;

    for (int i = 1; i <= n; i++) {
        if (used[i]) continue;
        int finishTime = now + job[i].t;
        if (finishTime > job[i].s) continue;

        used[i] = true;
        if (dfs(done + 1, finishTime)) return true;
        used[i] = false;
    }
    return false;
}

bool canStart(int startTime) {
    memset(used, 0, sizeof(used));
    return dfs(0, startTime);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    int maxS = 0;
    for (int i = 1; i <= n; i++) {
        cin >> job[i].t >> job[i].s;
        maxS = max(maxS, job[i].s);
    }

    for (int startTime = maxS; startTime >= 0; startTime--) {
        if (canStart(startTime)) {
            cout << startTime << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';
    return 0;
}
