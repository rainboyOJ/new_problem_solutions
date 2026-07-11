/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 19:28
 * update_at: 2026-07-11 19:30
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int T;

int bfs(int a, int b) {
    int limit = max(a, b) * 4 + 20;
    vector<int> dist(limit + 1, -1);
    queue<int> q;

    dist[a] = 0;
    q.push(a);

    while (!q.empty()) {
        int x = q.front();
        q.pop();

        if (x == b) return dist[x];

        int nxt[3];
        int cnt = 0;
        if (x + 1 <= limit) nxt[cnt++] = x + 1;
        if (x * 2 <= limit) nxt[cnt++] = x * 2;
        if (x % 2 == 0) nxt[cnt++] = x / 2;

        for (int i = 0; i < cnt; i++) {
            int y = nxt[i];
            if (y >= 1 && y <= limit && dist[y] == -1) {
                dist[y] = dist[x] + 1;
                q.push(y);
            }
        }
    }

    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        int a, b;
        cin >> a >> b;
        cout << bfs(a, b) << '\n';
    }

    return 0;
}
