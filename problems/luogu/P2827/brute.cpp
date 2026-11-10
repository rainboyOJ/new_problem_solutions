/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:43
 * update_at: 2026-11-11 00:43
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 暴力版本：使用 std::priority_queue
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q, u, v, t;
    if (!(cin >> n >> m >> q >> u >> v >> t)) return 0;

    priority_queue<int> pq;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        pq.push(x);
    }

    bool first_out = true;
    for (int i = 1; i <= m; ++i) {
        int max_val = pq.top();
        pq.pop();

        long long real_len = max_val + 1LL * (i - 1) * q;
        if (i % t == 0) {
            if (!first_out) cout << " ";
            cout << real_len;
            first_out = false;
        }

        long long part1 = real_len * u / v;
        long long part2 = real_len - part1;

        pq.push(static_cast<int>(part1 - 1LL * i * q));
        pq.push(static_cast<int>(part2 - 1LL * i * q));
    }
    cout << "\n";

    first_out = true;
    int total_worms = n + m;
    long long final_delta = 1LL * m * q;

    for (int rank = 1; rank <= total_worms; ++rank) {
        int val = pq.top();
        pq.pop();
        if (rank % t == 0) {
            if (!first_out) cout << " ";
            cout << val + final_delta;
            first_out = false;
        }
    }
    cout << "\n";

    return 0;
}
