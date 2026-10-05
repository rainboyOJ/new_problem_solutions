/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:30
 * update_at: 2026-10-05 23:30
 */
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 30;
const int SLOTS_PER_HOUR = 12; // 1 小时 = 12 个 5 分钟段

ll f[MAXN]; // 各湖第 1 个 5 分钟能钓到的鱼数
ll d[MAXN]; // 每多钓一段比上一段减少的鱼数
ll t[MAXN]; // 湖 i 到 i+1 的路程段数

// 在 1..m 号湖里钓满 slots 段，最多能钓到多少条鱼
ll best_catch(int m, int slots) {
    // 小根堆存 (负产量, 衰减量)，弹堆顶即当前产量最高的湖
    priority_queue<pair<ll, ll>, vector<pair<ll, ll> >, greater<pair<ll, ll> > > pq;
    for (int i = 1; i <= m; ++i) {
        pq.push(make_pair(-f[i], d[i]));
    }
    ll total = 0;
    for (int i = 0; i < slots; ++i) {
        pair<ll, ll> cur = pq.top();
        pq.pop();
        ll fish = -cur.first; // 该湖这一段的产量
        ll drop = cur.second; // 该湖的衰减量
        total += fish;
        ll nxt = fish - drop;
        if (nxt < 0) nxt = 0;
        pq.push(make_pair(-nxt, drop));
    }
    return total;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, H;
    if (!(cin >> n >> H)) return 0;
    for (int i = 1; i <= n; ++i) cin >> f[i];
    for (int i = 1; i <= n; ++i) cin >> d[i];
    for (int i = 1; i <= n - 1; ++i) cin >> t[i];

    ll best = 0;
    ll spent = 0; // 已走路程段数
    for (int L = 1; L <= n; ++L) {
        int slots = SLOTS_PER_HOUR * H - (int)spent;
        if (slots <= 0) break; // 路程耗光时间，更远的湖更亏
        best = max(best, best_catch(L, slots));
        spent += t[L];
    }
    cout << best << "\n";
    return 0;
}
