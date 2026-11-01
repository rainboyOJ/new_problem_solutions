/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-31 21:33
 * update_at: 2026-10-31 21:33
 */
// brute.cpp：逐起点 BFS，直接按题意数最短路，只适合 n<=300。
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAXN = 505;
ll n, d;
ll x[MAXN]; // 岛屿坐标
ll dist[MAXN]; // 当前起点到各点的最少步数，-1 表示尚未到达
ll ways[MAXN]; // 最短路条数，3 表示“至少三条”，避免真实条数过大溢出

void bfs(ll start) {
    fill(dist + 1, dist + n + 1, -1);
    fill(ways + 1, ways + n + 1, 0);
    queue<ll> pending;
    dist[start] = 0;
    ways[start] = 1;
    pending.push(start);
    while (!pending.empty()) {
        ll u = pending.front();
        pending.pop();
        for (ll v = 1; v <= n; v++) {
            if (v == u || abs(x[v] - x[u]) > d) continue;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                ways[v] = ways[u];
                pending.push(v);
            } else if (dist[v] == dist[u] + 1) {
                ways[v] = min(3LL, ways[v] + ways[u]);
            }
        }
    }
}

void solve() {
    scanf("%lld%lld", &n, &d);
    for (ll i = 1; i <= n; i++) scanf("%lld", &x[i]);
    ll answer = 0;
    for (ll start = 1; start <= n; start++) {
        bfs(start);
        for (ll end = start + 1; end <= n; end++) {
            if (ways[end] == 2) answer++;
        }
    }
    printf("%lld\n", answer);
}

int main() {
    ll c, tests;
    if (scanf("%lld%lld", &c, &tests) != 2) return 0;
    while (tests--) solve();
    return 0;
}
