// 2026-10-10 05:00
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;

const int MAXN = 500005;

vector<int> adj[MAXN];
int ts[MAXN];
int yts[MAXN];
int q_dist[MAXN];

int fa[MAXN];
int order[MAXN];
bool vis[MAXN];

ll cnt[MAXN];
ll ycnt[MAXN];
ll dis[MAXN];
ll dis2[MAXN];
ll ydis[MAXN];
ll ans[MAXN];

void solve() {
    int n, m, k, l, r;
    if (!(cin >> n >> m >> k >> l >> r)) return;

    for (int i = 1; i <= n; i++) {
        adj[i].clear();
        ts[i] = 0;
        yts[i] = 0;
        q_dist[i] = -1;
        vis[i] = false;
        cnt[i] = 0;
        ycnt[i] = 0;
        dis[i] = 0;
        dis2[i] = 0;
        ydis[i] = 0;
    }

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for (int i = 1; i <= m; i++) {
        int u;
        cin >> u;
        ts[u] = 1;
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (ts[i]) {
            q.push(i);
            q_dist[i] = 0;
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (q_dist[v] == -1) {
                q_dist[v] = q_dist[u] + 1;
                q.push(v);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (q_dist[i] >= l && q_dist[i] <= r) {
            yts[i] = 1;
        }
    }

    int head = 0, tail = 0;
    order[tail++] = 1;
    vis[1] = true;
    fa[1] = 0;

    while (head < tail) {
        int u = order[head++];
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = true;
                fa[v] = u;
                order[tail++] = v;
            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        int u = order[i];
        cnt[u] = ts[u];
        ycnt[u] = yts[u];
        for (int v : adj[u]) {
            if (v == fa[u]) continue;
            cnt[u] += cnt[v];
            ycnt[u] += ycnt[v];
            dis[u] += dis[v] + cnt[v];
            dis2[u] += dis2[v] + 2 * dis[v] + cnt[v];
            ydis[u] += ydis[v] + ycnt[v];
        }
    }

    ll total_cnt = cnt[1];
    ll total_ycnt = ycnt[1];

    for (int i = 0; i < n; i++) {
        int u = order[i];
        for (int v : adj[u]) {
            if (v == fa[u]) continue;
            ll rem_cnt = total_cnt - cnt[v];
            ll rem_dis = dis[u] - (dis[v] + cnt[v]);
            ll rem_dis2 = dis2[u] - (dis2[v] + 2 * dis[v] + cnt[v]);

            dis2[v] += rem_dis2 + 2 * rem_dis + rem_cnt;
            dis[v] += rem_dis + rem_cnt;

            ll rem_ycnt = total_ycnt - ycnt[v];
            ll rem_ydis = ydis[u] - (ydis[v] + ycnt[v]);

            ydis[v] += rem_ydis + rem_ycnt;
        }
    }

    for (int i = 1; i <= n; i++) {
        ans[i] = dis2[i] + ydis[i];
    }

    for (int i = 1; i <= k; i++) {
        int x;
        cin >> x;
        cout << ans[x] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
