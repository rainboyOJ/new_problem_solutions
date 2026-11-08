/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-17 01:40
 * update_at: 2026-07-17 01:40
 */
// brute.cpp：对每个点 s 做一次 BFS，求 s 能走到哪些点，用来对拍与理解题意。
// 关键点：到自己的可达性要看是否存在从 s 出发、回到 s 的回路（走至少一条边）。
#include <bits/stdc++.h>
using namespace std;

const int N = 105;

int n;
bool edge[N][N];
bool can[N][N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) {
            int x;
            cin >> x;
            edge[i][j] = (x == 1);
        }

    for (int s = 1; s <= n; s++) {
        // 从 s 的所有出边出发做 BFS；若过程中回到 s，说明 s 能绕一圈到自己
        vector<int> q;
        vector<bool> vis(n + 1, false);
        for (int v = 1; v <= n; v++)
            if (edge[s][v]) {
                q.push_back(v);
                vis[v] = true;
            }
        for (size_t head = 0; head < q.size(); head++) {
            int u = q[head];
            for (int v = 1; v <= n; v++)
                if (edge[u][v] && !vis[v]) {
                    vis[v] = true;
                    q.push_back(v);
                }
        }
        for (int v = 1; v <= n; v++)
            if (v != s && vis[v]) can[s][v] = true;
        can[s][s] = vis[s];               // 只有回路可达自己时才为 true
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j > 1) cout << ' ';
            cout << (can[i][j] ? 1 : 0);
        }
        cout << '\n';
    }

    return 0;
}
