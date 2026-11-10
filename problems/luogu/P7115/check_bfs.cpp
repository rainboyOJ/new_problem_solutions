#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

struct State {
    vector<vector<int>> p;
    bool operator<(const State& o) const {
        return p < o.p;
    }
};

int n, m;

bool is_solved(const State& s) {
    for (int i = 0; i <= n; ++i) {
        if (s.p[i].empty()) continue;
        if (s.p[i].size() != (size_t)m) return false;
        int c = s.p[i][0];
        for (int x : s.p[i]) if (x != c) return false;
    }
    return true;
}

vector<pair<int, int>> bfs_solve(const State& start) {
    queue<State> q;
    map<State, int> dist;
    map<State, pair<State, pair<int, int>>> prev_op;

    q.push(start);
    dist[start] = 0;

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (is_solved(cur)) {
            vector<pair<int, int>> path;
            State s = cur;
            while (s.p != start.p) {
                auto p = prev_op[s];
                path.push_back(p.second);
                s = p.first;
            }
            reverse(path.begin(), path.end());
            return path;
        }

        // 剪枝限制
        if (dist[cur] >= 10) continue;

        for (int i = 0; i <= n; ++i) {
            if (cur.p[i].empty()) continue;
            for (int j = 0; j <= n; ++j) {
                if (i == j || cur.p[j].size() == (size_t)m) continue;
                State nxt = cur;
                int ball = nxt.p[i].back();
                nxt.p[i].pop_back();
                nxt.p[j].push_back(ball);

                if (!dist.count(nxt)) {
                    dist[nxt] = dist[cur] + 1;
                    prev_op[nxt] = {cur, {i, j}};
                    q.push(nxt);
                }
            }
        }
    }
    return {};
}

int main() {
    cin >> n >> m;
    State start;
    start.p.resize(n + 1);
    for (int i = 0; i < n; ++i) {
        start.p[i].resize(m);
        for (int j = 0; j < m; ++j) cin >> start.p[i][j];
    }
    auto path = bfs_solve(start);
    cout << "Path size: " << path.size() << endl;
    for (auto p : path) {
        cout << p.first + 1 << " " << p.second + 1 << endl;
    }
    return 0;
}
