/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:36
 * update_at: 2026-07-11 17:37
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

bool all_equal(vector<int> state) {
    for (int i = 1; i < (int)state.size(); i++) {
        if (state[i] != state[0]) {
            return false;
        }
    }
    return true;
}

int bfs_solve(vector<int> start) {
    queue<vector<int> > q;
    map<vector<int>, int> dis;

    q.push(start);
    dis[start] = 0;

    while (!q.empty()) {
        vector<int> cur = q.front();
        q.pop();

        int d = dis[cur];
        if (all_equal(cur)) {
            return d;
        }

        int len = (int)cur.size();
        for (int i = 0; i + 1 < len; i++) {
            vector<int> nxt;
            for (int j = 0; j < len; j++) {
                if (j == i) {
                    nxt.push_back(cur[j] + cur[j + 1]);
                    j++;
                } else {
                    nxt.push_back(cur[j]);
                }
            }

            if (dis.find(nxt) == dis.end()) {
                dis[nxt] = d + 1;
                q.push(nxt);
            }
        }
    }

    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> a;
        for (int i = 1; i <= n; i++) {
            int x;
            cin >> x;
            a.push_back(x);
        }

        cout << bfs_solve(a) << '\n';
    }

    return 0;
}
