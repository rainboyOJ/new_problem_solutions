#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Task {
    int t, w;
    bool operator<(const Task& other) const {
        if (t != other.t)
            return t < other.t;
        return w > other.w;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Task> tasks(n);
    for (int i = 0; i < n; ++i) {
        cin >> tasks[i].t >> tasks[i].w;
    }

    sort(tasks.begin(), tasks.end());

    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < n; ++i) {
        if (pq.size() < tasks[i].t) {
            pq.push(tasks[i].w);
        } else if (!pq.empty() && pq.top() < tasks[i].w) {
            pq.pop();
            pq.push(tasks[i].w);
        }
    }

    long long max_reward = 0;
    while (!pq.empty()) {
        max_reward += pq.top();
        pq.pop();
    }

    cout << max_reward << "\n";

    return 0;
}
