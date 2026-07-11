/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 14:17
 * update_at: 2026-07-11 14:19
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int n;
string a, b;

int greedy_answer() {
    int ans = 0;
    bool in_bad_segment = false;

    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            if (!in_bad_segment) {
                ans++;
                in_bad_segment = true;
            }
        } else {
            in_bad_segment = false;
        }
    }

    return ans;
}

int bfs_brute() {
    int start = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            start |= (1 << i);
        }
    }

    int total = 1 << n;
    vector<int> dist(total, -1);
    queue<int> q;

    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int state = q.front();
        q.pop();

        if (state == 0) {
            return dist[state];
        }

        // 枚举一次操作翻转的连续子串。
        for (int l = 0; l < n; l++) {
            int mask = 0;
            for (int r = l; r < n; r++) {
                mask |= (1 << r);
                int next_state = state ^ mask;
                if (dist[next_state] == -1) {
                    dist[next_state] = dist[state] + 1;
                    q.push(next_state);
                }
            }
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> a >> b;

    // BFS 只用于小数据对拍；大数据退回到贪心，避免暴力数组过大。
    if (n <= 12) {
        cout << bfs_brute() << '\n';
    } else {
        cout << greedy_answer() << '\n';
    }

    return 0;
}
