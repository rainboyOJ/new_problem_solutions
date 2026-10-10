/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const char* NO_ROUND_TRIP = "Round trip does not exist.";

// 路口邻接表：(街道编号, 另一端路口)，按街道编号升序
map<int, vector<pair<int, int> > > adj;
set<int> used_street;      // 已走过的街道编号
map<int, int> pos;         // 各路口扫描到邻接表的下标

// Hierholzer：从 start 出发走遍每条街道一次，返回字典序最小的街道序列
vector<int> euler_tour(int start) {
    vector<int> route;
    // 栈：(路口, 进入该路口所走的街道)，0 为哨兵
    vector<pair<int, int> > stack;
    stack.push_back(make_pair(start, 0));
    while (!stack.empty()) {
        int u = stack.back().first;
        int entered = stack.back().second;
        vector<pair<int, int> >& edges = adj[u];
        int i = pos[u];
        while (i < (int)edges.size() && used_street.count(edges[i].first)) i++;
        if (i < (int)edges.size()) {
            int street = edges[i].first;
            int v = edges[i].second;
            pos[u] = i + 1;
            used_street.insert(street);
            stack.push_back(make_pair(v, street));
        } else {
            pos[u] = i;
            stack.pop_back();
            if (entered) route.push_back(entered);
        }
    }
    reverse(route.begin(), route.end());
    return route;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> out;
    while (true) {
        adj.clear();
        used_street.clear();
        pos.clear();
        // 读一组边的 (x, y, street)
        vector<tuple<int, int, int> > edges;
        int x, y, z;
        bool first = true;
        while (true) {
            if (!(cin >> x >> y)) {
                // 输入结束
                if (edges.empty() && first) {
                    // 直接结束
                    goto done;
                }
                break;
            }
            first = false;
            if (x == 0 && y == 0) break;
            cin >> z;
            edges.push_back(make_tuple(x, y, z));
        }
        if (edges.empty()) break;

        int start = min(get<0>(edges[0]), get<1>(edges[0]));
        for (size_t i = 0; i < edges.size(); i++) {
            int a = get<0>(edges[i]), b = get<1>(edges[i]), s = get<2>(edges[i]);
            adj[a].push_back(make_pair(s, b));
            adj[b].push_back(make_pair(s, a));
        }
        for (map<int, vector<pair<int, int> > >::iterator it = adj.begin(); it != adj.end(); ++it)
            sort(it->second.begin(), it->second.end());

        // 连通性（从 start 出发）
        set<int> seen;
        vector<int> frontier;
        seen.insert(start);
        frontier.push_back(start);
        while (!frontier.empty()) {
            int u = frontier.back(); frontier.pop_back();
            for (size_t i = 0; i < adj[u].size(); i++) {
                int v = adj[u][i].second;
                if (!seen.count(v)) {
                    seen.insert(v);
                    frontier.push_back(v);
                }
            }
        }
        bool all_even = true;
        for (map<int, vector<pair<int, int> > >::iterator it = adj.begin(); it != adj.end(); ++it) {
            if (it->second.size() % 2 != 0) { all_even = false; break; }
        }
        bool connected = (seen.size() == adj.size());

        if (all_even && connected) {
            vector<int> route = euler_tour(start);
            string s;
            for (size_t i = 0; i < route.size(); i++) {
                if (i) s += " ";
                s += to_string(route[i]);
            }
            out.push_back(s);
        } else {
            out.push_back(NO_ROUND_TRIP);
        }
    }
done:
    for (size_t i = 0; i < out.size(); i++) cout << out[i] << "\n";
    return 0;
}
