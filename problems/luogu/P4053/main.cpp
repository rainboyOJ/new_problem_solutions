#include <bits/stdc++.h>
using namespace std;

const int MAXN = 150005;

struct Building {
    long long need_time;
    long long deadline;
};

int n;
Building buildings[MAXN];

bool cmp_building(const Building &a, const Building &b) {
    if (a.deadline != b.deadline) {
        return a.deadline < b.deadline;
    }
    return a.need_time < b.need_time;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> buildings[i].need_time >> buildings[i].deadline;
    }

    sort(buildings + 1, buildings + n + 1, cmp_building);

    priority_queue<long long> selected;
    long long total_time = 0;

    for (int i = 1; i <= n; i++) {
        total_time += buildings[i].need_time;
        selected.push(buildings[i].need_time);

        if (total_time > buildings[i].deadline) {
            total_time -= selected.top();
            selected.pop();
        }
    }

    cout << selected.size() << '\n';
    return 0;
}
