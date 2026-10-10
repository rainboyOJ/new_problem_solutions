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

const ll INF = 0x3f3f3f3f3f3f3f3fLL;

int n, m;
int slots[25];            // 各槽位的 C 值
int start_slot;           // 手柄初始槽（C=0）
ll dist[1005][25];        // dist[楼层][槽位]

void solve() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> slots[i];
        if (slots[i] == 0) start_slot = i;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < m; j++)
            dist[i][j] = INF;

    dist[1][start_slot] = 0;
    priority_queue<pair<ll, pair<int, int> >,
                   vector<pair<ll, pair<int, int> > >,
                   greater<pair<ll, pair<int, int> > > > pq;
    pq.push(make_pair(0LL, make_pair(1, start_slot)));

    while (!pq.empty()) {
        ll d = pq.top().first;
        int floor = pq.top().second.first;
        int slot = pq.top().second.second;
        pq.pop();
        if (floor == n) {   // 第一次弹出 N 层即最优
            cout << d << "\n";
            return;
        }
        if (d > dist[floor][slot]) continue;
        for (int j = 0; j < m; j++) {   // 扳到槽 j
            int nf = floor + slots[j];
            if (nf < 1 || nf > n) continue;
            ll nd = d + (ll)abs(slot - j) + 2LL * (ll)abs(slots[j]);
            if (nd < dist[nf][j]) {
                dist[nf][j] = nd;
                pq.push(make_pair(nd, make_pair(nf, j)));
            }
        }
    }
    cout << "-1\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
