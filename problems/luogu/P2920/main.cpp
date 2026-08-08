#include <bits/stdc++.h>
using namespace std;

struct Job {
    int t;
    int s;
};

Job job[1005];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> job[i].t >> job[i].s;
    }

    sort(job + 1, job + n + 1, [](const Job &a, const Job &b) {
        return a.s > b.s;
    });

    int now = job[1].s;
    for (int i = 1; i <= n; i++) {
        // 当前任务必须不晚于自己的截止时间完成，也不能晚于后面任务留出的时间。
        if (now > job[i].s) now = job[i].s;
        now -= job[i].t;
    }

    if (now < 0) {
        cout << -1 << '\n';
    } else {
        cout << now << '\n';
    }

    return 0;
}
