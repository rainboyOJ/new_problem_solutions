#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

struct Job {
    long long deadline;
    long long profit;
};

int n;
Job jobs[MAXN];

bool cmp_job(const Job &a, const Job &b) {
    if (a.deadline != b.deadline) {
        return a.deadline < b.deadline;
    }
    return a.profit > b.profit;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> jobs[i].deadline >> jobs[i].profit;
    }

    sort(jobs + 1, jobs + n + 1, cmp_job);

    priority_queue<long long, vector<long long>, greater<long long> > selected;
    long long ans = 0;

    for (int i = 1; i <= n; i++) {
        selected.push(jobs[i].profit);
        ans += jobs[i].profit;

        if ((long long)selected.size() > jobs[i].deadline) {
            ans -= selected.top();
            selected.pop();
        }
    }

    cout << ans << '\n';
    return 0;
}
