/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 18:38
 * update_at: 2026-07-11 18:42
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 300005;

int n, k;
ll t[MAXN];
bool can_interview[MAXN];

void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }

    priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
    for (int i = 0; i < k; i++) {
        pq.push(make_pair(t[i], i));
    }

    int next_cow = k;
    ll bessie_time = 0;
    int first_farmer = 0;
    vector<vector<int> > events;

    while (true) {
        pair<ll, int> first = pq.top();
        pq.pop();

        vector<pair<ll, int> > event;
        event.push_back(first);

        while (!pq.empty() && pq.top().first == first.first) {
            event.push_back(pq.top());
            pq.pop();
        }

        if ((int)event.size() > 1) {
            vector<int> farmers;
            for (int i = 0; i < (int)event.size(); i++) {
                farmers.push_back(event[i].second);
            }
            events.push_back(farmers);
        }

        if (next_cow + (int)event.size() > n) {
            bessie_time = first.first;
            first_farmer = event[0].second;
            break;
        }

        for (int i = 0; i < (int)event.size(); i++) {
            int farmer = event[i].second;
            pq.push(make_pair(first.first + t[next_cow], farmer));
            next_cow++;
        }
    }

    cout << bessie_time << '\n';

    for (int i = 0; i < k; i++) {
        can_interview[i] = false;
    }
    can_interview[first_farmer] = true;

    // 从后往前传播：若某个同时完成事件里已有可能农夫，则同事件农夫都可能。
    for (int i = (int)events.size() - 1; i >= 0; i--) {
        bool has_possible = false;
        for (int j = 0; j < (int)events[i].size(); j++) {
            if (can_interview[events[i][j]]) {
                has_possible = true;
            }
        }
        if (has_possible) {
            for (int j = 0; j < (int)events[i].size(); j++) {
                can_interview[events[i][j]] = true;
            }
        }
    }

    for (int i = 0; i < k; i++) {
        cout << (can_interview[i] ? '1' : '0');
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
