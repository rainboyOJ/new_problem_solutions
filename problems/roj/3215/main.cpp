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

// 每条高铁路线建成一条有向边：开头车次 -> 末尾车次
// 边上存 a = (n+1)*(2*速度和) + 1

int n;                       // 车次种类数（节点数）
vector<pair<int, ll> > adj[5005];

// 判断是否存在平均值 >= r - 0.5 的环：对边权 a - (n+1)*(2r-1) 判严格正环
bool has_cycle_avg_ge(int r) {
    // 边权 a - (n+1)*(2r-1)
    ll offset = (ll)(n + 1) * (2LL * r - 1);
    // 复制一份偏移后的图判断正环
    // 直接改全局 adj 不方便，这里重新做一次 SPFA
    vector<ll> dist(n, 0);
    vector<int> edge_cnt(n, 0);
    vector<char> in_queue(n, 1);
    deque<int> q;
    for (int i = 0; i < n; i++) q.push_back(i);
    while (!q.empty()) {
        int u = q.front(); q.pop_front();
        in_queue[u] = 0;
        ll du = dist[u];
        for (size_t i = 0; i < adj[u].size(); i++) {
            int v = adj[u][i].first;
            ll a = adj[u][i].second;
            ll nd = du + a - offset;
            if (nd > dist[v]) {
                dist[v] = nd;
                edge_cnt[v] = edge_cnt[u] + 1;
                if (edge_cnt[v] >= n) return true;
                if (!in_queue[v]) {
                    if (!q.empty() && nd > dist[q.front()]) q.push_front(v);
                    else q.push_back(v);
                    in_queue[v] = 1;
                }
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> m;
    cin.ignore();

    map<string, int> node_id;
    vector<pair<string, string> > raw;   // 每条路线 (开头车次, 末尾车次)
    vector<int> raw_s;                   // 每条路线的速度和

    for (int line = 0; line < m; line++) {
        string s;
        getline(cin, s);
        // 拆成 codes
        vector<string> codes;
        string cur;
        for (size_t i = 0; i <= s.size(); i++) {
            if (i == s.size() || s[i] == '-') {
                codes.push_back(cur);
                cur.clear();
            } else {
                cur.push_back(s[i]);
            }
        }
        int sum = 0;
        for (size_t i = 0; i < codes.size(); i++) {
            char c = codes[i][0];
            if (c == 'S') sum += 1000;
            else if (c == 'G') sum += 500;
            else if (c == 'D') sum += 300;
            else if (c == 'T') sum += 200;
            else if (c == 'K') sum += 150;
        }
        raw.push_back(make_pair(codes[0], codes[codes.size() - 1]));
        raw_s.push_back(sum);
        if (node_id.find(codes[0]) == node_id.end())
            node_id[codes[0]] = (int)node_id.size();
        if (node_id.find(codes[codes.size() - 1]) == node_id.end())
            node_id[codes[codes.size() - 1]] = (int)node_id.size();
    }

    n = (int)node_id.size();
    ll scale = n + 1;
    for (size_t i = 0; i < raw.size(); i++) {
        int u = node_id[raw[i].first];
        int v = node_id[raw[i].second];
        adj[u].push_back(make_pair(v, scale * 2LL * raw_s[i] + 1));
    }

    int lo = 1, hi = 20001;
    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (has_cycle_avg_ge(mid)) lo = mid + 1;
        else hi = mid;
    }
    int ans = (lo > 1) ? lo - 1 : -1;
    cout << ans << "\n";
    return 0;
}
