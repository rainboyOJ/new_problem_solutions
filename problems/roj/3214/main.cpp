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

const int HOURS = 24;
const int SHIFT = 8;
const ll NEG = -1000000000LL;

int need[25];
int hired[25];

// 总雇佣人数为 total 时是否存在满足需求的排班：SPFA 判正环
bool shift_ok(int total) {
    vector<pair<int, ll> > edges[25];
    for (int i = 0; i < HOURS; i++) {
        edges[i].push_back(make_pair(i + 1, 0LL));
        edges[i + 1].push_back(make_pair(i, -(ll)hired[i]));
    }
    for (int i = SHIFT; i <= HOURS; i++)
        edges[i - SHIFT].push_back(make_pair(i, (ll)need[i - 1]));
    for (int i = 1; i < SHIFT; i++)
        edges[i + 16].push_back(make_pair(i, (ll)need[i - 1] - total));
    edges[0].push_back(make_pair(HOURS, (ll)total));
    edges[HOURS].push_back(make_pair(0, -(ll)total));

    ll dist[25];
    int relax_count[25];
    bool in_queue[25];
    for (int i = 0; i <= HOURS; i++) {
        dist[i] = NEG; relax_count[i] = 0; in_queue[i] = false;
    }
    dist[0] = 0; in_queue[0] = true;
    deque<int> q;
    q.push_back(0);

    while (!q.empty()) {
        int u = q.front(); q.pop_front();
        in_queue[u] = false;
        ll du = dist[u];
        for (size_t i = 0; i < edges[u].size(); i++) {
            int v = edges[u][i].first;
            ll w = edges[u][i].second;
            if (du + w > dist[v]) {
                dist[v] = du + w;
                relax_count[v]++;
                if (relax_count[v] >= HOURS + 1) return false; // 存在正环
                if (!in_queue[v]) {
                    in_queue[v] = true;
                    q.push_back(v);
                }
            }
        }
    }
    return true;
}

int min_cashiers(int total_applicants) {
    int low = 0, high = total_applicants, answer = -1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (shift_ok(mid)) {
            answer = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // 与 main.py 一致：把输入全部读成 token，格式不符（非本组数据）时提前停止，
    // 已读到的组仍照常输出。
    vector<int> tokens;
    int x;
    while (cin >> x) tokens.push_back(x);

    size_t idx = 0;
    if (tokens.empty()) return 0;
    int T = tokens[idx++];
    vector<string> out;

    for (int case_ = 0; case_ < T; case_++) {
        // 读 24 个需求
        if (idx + HOURS > tokens.size()) break;
        for (int i = 0; i < HOURS; i++) need[i] = tokens[idx++];
        if (idx >= tokens.size()) break;
        int nn = tokens[idx++];
        if (idx + nn > tokens.size()) break;
        for (int i = 0; i < HOURS; i++) hired[i] = 0;
        bool valid = true;
        for (int i = 0; i < nn; i++) {
            int t = tokens[idx++];
            if (t < 0 || t >= HOURS) { valid = false; break; }
            hired[t]++;
        }
        if (!valid) break;
        int sum = 0;
        for (int i = 0; i < HOURS; i++) sum += hired[i];
        int best = min_cashiers(sum);
        out.push_back(best < 0 ? "No Solution" : to_string(best));
    }
    for (size_t i = 0; i < out.size(); i++) cout << out[i] << "\n";
    if (out.empty()) cout << "\n";
    return 0;
}
