/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:52
 * update_at: 2026-11-11 00:52
 */
// brute.cpp：小规模使用 STL 优先队列作为对拍基准
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    priority_queue<long long, vector<long long>, greater<long long>> pq;
    for (int i = 0; i < n; ++i) {
        long long x;
        cin >> x;
        pq.push(x);
    }

    long long ans = 0;
    while (pq.size() > 1) {
        long long u = pq.top();
        pq.pop();
        long long v = pq.top();
        pq.pop();
        ans += (u + v);
        pq.push(u + v);
    }

    cout << ans << "\n";

    return 0;
}
