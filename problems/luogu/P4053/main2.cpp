/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-10 17:19
 * update_at: 2026-08-10 17:19
 */
// main2.cpp：手写堆版本，风格对齐 rbook 的 heap 模板（h[0] 不使用，up/down 维护堆序）。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 150005;

struct Building {
    long long need_time;
    long long deadline;
};

int n;
Building buildings[MAXN];

// 最大堆：手写实现，风格对齐 rbook 的 heap 模板（h[0] 不使用）。
template <typename T>
struct MaxHeap {
    vector<T> h;

    MaxHeap() {
        h.push_back(T());
    }

    int size() const {
        return (int)h.size() - 1;
    }

    bool empty() const {
        return size() == 0;
    }

    T top() const {
        return h[1];
    }

    void up(int u) {
        while (u > 1 && h[u] > h[u / 2]) {
            swap(h[u], h[u / 2]);
            u /= 2;
        }
    }

    void down(int u) {
        while (true) {
            int best = u;
            int left = u * 2;
            int right = u * 2 + 1;

            if (left <= size() && h[left] > h[best]) best = left;
            if (right <= size() && h[right] > h[best]) best = right;
            if (best == u) break;

            swap(h[u], h[best]);
            u = best;
        }
    }

    void push(const T &x) {
        h.push_back(x);
        up(size());
    }

    void pop() {
        if (empty()) return;
        h[1] = h.back();
        h.pop_back();
        if (!empty()) down(1);
    }
};

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

    MaxHeap<long long> selected; // 已选任务的工期，堆顶是最大的那个
    long long total_time = 0;    // 已选任务的总工期

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
