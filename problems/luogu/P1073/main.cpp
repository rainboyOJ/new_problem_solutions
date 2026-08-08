#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;
const int MAXE = 1000005;
const int INF = 1000000000;

int n, m;
int price_city[MAXN];

int head[MAXN], to[MAXE], nxt[MAXE], edge_cnt;
int rev_head[MAXN], rev_to[MAXE], rev_nxt[MAXE], rev_edge_cnt;

int min_buy[MAXN];  // min_buy[x] 表示从 1 到 x 的某条路线上能遇到的最低价格。
int max_sell[MAXN]; // max_sell[x] 表示从 x 到 n 的某条路线上能遇到的最高价格。
bool in_queue[MAXN];

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;

    rev_edge_cnt++;
    rev_to[rev_edge_cnt] = u;
    rev_nxt[rev_edge_cnt] = rev_head[v];
    rev_head[v] = rev_edge_cnt;
}

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> price_city[i];
    }

    for (int i = 1; i <= m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        add_edge(x, y);
        if (z == 2) {
            add_edge(y, x);
        }
    }
}

void calc_min_buy() {
    for (int i = 1; i <= n; i++) {
        min_buy[i] = INF;
        in_queue[i] = false;
    }

    queue<int> que;
    min_buy[1] = price_city[1];
    que.push(1);
    in_queue[1] = true;

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        in_queue[u] = false;

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            int value = min(min_buy[u], price_city[v]);
            if (value < min_buy[v]) {
                min_buy[v] = value;
                if (!in_queue[v]) {
                    que.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }
}

void calc_max_sell() {
    for (int i = 1; i <= n; i++) {
        max_sell[i] = -INF;
        in_queue[i] = false;
    }

    queue<int> que;
    max_sell[n] = price_city[n];
    que.push(n);
    in_queue[n] = true;

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        in_queue[u] = false;

        for (int i = rev_head[u]; i != 0; i = rev_nxt[i]) {
            int v = rev_to[i];
            int value = max(max_sell[u], price_city[v]);
            if (value > max_sell[v]) {
                max_sell[v] = value;
                if (!in_queue[v]) {
                    que.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }
}

void solve() {
    calc_min_buy();
    calc_max_sell();

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        if (min_buy[i] == INF || max_sell[i] == -INF) {
            continue;
        }
        answer = max(answer, max_sell[i] - min_buy[i]);
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
