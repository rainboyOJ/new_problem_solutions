#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MAXN = 10005;
const ll MAXM = 20005;
const ll INF = (1LL << 60);

ll n, m, k;
ll dis[MAXN][105];
bool in_que[MAXN][105];

struct Node {
    ll u, mod;
};

struct LinkList {
    struct Edge {
        ll u, v, w, next;
    };

    Edge e[MAXM];
    ll h[MAXN], edge_cnt;

    LinkList() {
        edge_cnt = 0;
        memset(h, -1, sizeof(h));
    }

    void add(ll u, ll v, ll w = 0) {
        e[edge_cnt] = {u, v, w, h[u]};
        h[u] = edge_cnt++;
    }

    Edge &operator[](ll i) {
        return e[i];
    }
} graph;

queue<Node> q;

bool update(ll u, ll mod, ll val) {
    if (dis[u][mod] > val) {
        dis[u][mod] = val;
        return true;
    }
    return false;
}

void init() {
    cin >> n >> m >> k;
    for (ll i = 1; i <= m; ++i) {
        ll u, v, a;
        cin >> u >> v >> a;
        graph.add(u, v, a);
    }

    for (ll i = 0; i < MAXN; ++i) {
        for (ll j = 0; j < 105; ++j) {
            dis[i][j] = INF;
        }
    }
    dis[1][0] = 0;
}

void spfa() {
    q.push({1, 0});
    in_que[1][0] = true;

    while (!q.empty()) {
        ll u = q.front().u;
        ll mod = q.front().mod;
        q.pop();
        in_que[u][mod] = false;

        ll d = dis[u][mod];

        for (ll i = graph.h[u]; i != -1; i = graph[i].next) {
            ll v = graph[i].v;
            ll open_time = graph[i].w;

            ll len = d;
            if (len < open_time) {
                ll cnt = (open_time - len + k - 1) / k;
                len += cnt * k;
            }

            ++len;
            ll v_mod = len % k;

            if (update(v, v_mod, len)) {
                if (!in_que[v][v_mod]) {
                    in_que[v][v_mod] = true;
                    q.push({v, v_mod});
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init();
    spfa();

    if (dis[n][0] == INF) {
        cout << -1 << '\n';
    } else {
        cout << dis[n][0] << '\n';
    }

    return 0;
}
