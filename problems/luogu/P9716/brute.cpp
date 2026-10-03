/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:23
 * update_at: 2026-10-03 12:30
 *
 * P9716 的暴力解，用来对拍验证 main.cpp。
 *
 * 思路：完全不利用题目结构，直接把「每个元素的颜色」当成状态。
 * 用一个 n 位二进制数 S 表示哪些元素的颜色是 1（0 下标，第 i 位是 c_i）。
 * 初始状态是 S = (1 << s)。
 * 一次操作 c_i <- c_{a_i} 就是从状态 S 走到新状态 S'（代价 p_i）：
 *   - 若 a_i 的颜色是 1：S' = S | (1 << i)
 *   - 否则：            S' = S & ~(1 << i)
 * 这等价于一张有 2^n 个点、每个点 n 条出边的图，边权 p_i >= 0，
 * 于是用 Dijkstra 求出从初始状态到每个状态的最小代价 dist[S]。
 * 最终答案 = max_S ( sum_{i 在 S 中} w_i - dist[S] )。
 *
 * 状态数 2^n 是指数级，所以只能跑很小的 n，但正确性没有任何疑问。
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 18;          // brute 只能处理很小的 n（2^n 个状态）
const ll INF = (ll)4e18;

int n, s;
ll w[MAXN], p[MAXN];
int a[MAXN];

ll dist_[1 << MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n >> s)) return 0;
    s--;
    for (int i = 0; i < n; i++) cin >> w[i];
    for (int i = 0; i < n; i++) cin >> p[i];
    for (int i = 0; i < n; i++) { cin >> a[i]; a[i]--; }

    int total = 1 << n;
    for (int S = 0; S < total; S++) dist_[S] = INF;

    int start = 1 << s;
    dist_[start] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        ll d = pq.top().first;
        int S = pq.top().second;
        pq.pop();
        if (d > dist_[S]) continue;
        for (int i = 0; i < n; i++) {
            int T;
            if ((S >> a[i]) & 1) T = S | (1 << i);      // a_i 是 1 -> i 变 1
            else                 T = S & ~(1 << i);     // a_i 是 0 -> i 变 0
            if (T == S) continue;                       // 颜色没变，这一手白花钱
            ll nd = d + p[i];
            if (nd < dist_[T]) {
                dist_[T] = nd;
                pq.push({nd, T});
            }
        }
    }

    ll ans = -INF;
    for (int S = 0; S < total; S++) {
        if (dist_[S] == INF) continue;
        ll val = -dist_[S];
        for (int i = 0; i < n; i++) if ((S >> i) & 1) val += w[i];
        if (val > ans) ans = val;
    }
    cout << ans << "\n";
    return 0;
}
