#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

// 状态：n+1 根柱子，每根柱子是 vector<int>
struct State {
    vector<vector<int>> p;
    bool operator<(const State& o) const {
        return p < o.p;
    }
};

int main() {
    int n = 2, m = 3;
    State start;
    start.p.resize(3);
    start.p[0] = {1, 1, 2};
    start.p[1] = {2, 1, 2};
    start.p[2] = {};

    queue<State> q;
    map<State, int> dist;
    map<State, pair<State, pair<int, int>>> prev_op;

    q.push(start);
    dist[start] = 0;

    auto is_target = [&](const State& s) {
        for (int i = 0; i < 3; ++i) {
            if (s.p[i].empty()) continue;
            if (s.p[i].size() != m) return false;
            int col = s.p[i][0];
            for (int x : s.p[i]) if (x != col) return false;
        }
        return true;
    };

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        if (is_target(cur)) {
            cout << "Min steps: " << dist[cur] << endl;
            vector<pair<int, int>> path;
            State s = cur;
            while (s.p != start.p) {
                auto p = prev_op[s];
                path.push_back(p.second);
                s = p.first;
            }
            reverse(path.begin(), path.end());
            for (auto step : path) {
                cout << step.first + 1 << " " << step.second + 1 << endl;
            }
            return 0;
        }

        for (int i = 0; i < 3; ++i) {
            if (cur.p[i].empty()) continue;
            for (int j = 0; j < 3; ++j) {
                if (i == j || cur.p[j].size() == m) continue;
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
    return 0;
}
