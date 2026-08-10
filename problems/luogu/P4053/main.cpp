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

    // 大根堆：priority_queue 默认堆顶最大，堆顶就是已选任务中最长的工期。
    priority_queue<long long> selected;
    long long total_time = 0; // 已选任务的总工期

    for (int i = 1; i <= n; i++) {
        total_time += buildings[i].need_time;
        selected.push(buildings[i].need_time);

        // 当前任务超时：扔掉已选任务中工期最长的，给后续留余量。
        if (total_time > buildings[i].deadline) {
            total_time -= selected.top();
            selected.pop();
        }
    }

    cout << selected.size() << '\n';
    return 0;
}
