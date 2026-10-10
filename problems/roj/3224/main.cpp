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

const int NO_EDGE = -1;
const int UNREACHED = -1;

int head[205];
vector<int> to, nxt;
vector<ll> cap;

void add_edge(int u, int v, ll c) {
    to.push_back(v); cap.push_back(c); nxt.push_back(head[u]); head[u] = (int)to.size() - 1;
    to.push_back(u); cap.push_back(0); nxt.push_back(head[v]); head[v] = (int)to.size() - 1;
}

int level[205];

// BFS 分层
bool build_levels(int s, int t, int m) {
    for (int i = 1; i <= m; i++) level[i] = UNREACHED;
    level[s] = 0;
    deque<int> q;
    q.push_back(s);
    while (!q.empty()) {
        int u = q.front(); q.pop_front();
        int e = head[u];
        while (e != NO_EDGE) {
            int v = to[e];
            if (cap[e] > 0 && level[v] == UNREACHED) {
                level[v] = level[u] + 1;
                q.push_back(v);
            }
            e = nxt[e];
        }
    }
    return level[t] != UNREACHED;
}

// 在当前分层图上推阻塞流
ll blocking_flow(int s, int t) {
    vector<int> it(head, head + 205);
    vector<pair<int, int> > path;   // (点, 走出的弧号)
    ll flow = 0;
    int u = s;
    while (true) {
        if (u == t) {
            ll bottle = 1LL << 60;
            for (size_t i = 0; i < path.size(); i++)
                bottle = min(bottle, cap[path[i].second]);
            for (size_t i = 0; i < path.size(); i++) {
                cap[path[i].second] -= bottle;
                cap[path[i].second ^ 1] += bottle;
            }
            flow += bottle;
            size_t first = 0;
            while (first < path.size() && cap[path[first].second] != 0) first++;
            path.resize(first);
            u = path.empty() ? s : to[path.back().second];
        } else {
            int e = it[u];
            int advance = NO_EDGE;
            while (e != NO_EDGE) {
                int v = to[e];
                if (cap[e] > 0 && level[v] == level[u] + 1) { advance = e; break; }
                e = nxt[e];
            }
            it[u] = e;
            if (advance != NO_EDGE) {
                path.push_back(make_pair(u, advance));
                u = to[advance];
            } else if (path.empty()) {
                break;
            } else {
                level[u] = UNREACHED;
                u = path.back().first;
                path.pop_back();
            }
        }
    }
    return flow;
}

ll max_flow(int s, int t, int m) {
    ll flow = 0;
    while (build_levels(s, t, m)) {
        flow += blocking_flow(s, t);
    }
    return flow;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    int s = 1, t = m;
    for (int i = 1; i <= m; i++) head[i] = NO_EDGE;
    for (int i = 0; i < n; i++) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        add_edge(u, v, c);
    }
    cout << max_flow(s, t, m) << "\n";
    return 0;
}
