// brute.cpp：对每头有牛的大写牧场各跑一次 Dijkstra，直接比较谁到 Z 最近。
// 小数据下很好理解，也方便对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 52;
const int MAXM = 4005;
const int INF = 1e9;

struct HeapNode {
    int u;
    int dist;

    bool operator < (const HeapNode &other) const {
        return dist > other.dist;
    }
};

int p;
int head[MAXN], to[MAXM], nxt[MAXM], w[MAXM], edge_cnt;
int dist_arr[MAXN];
bool vis[MAXN];

int char_to_id(char ch) {
    if ('a' <= ch && ch <= 'z') {
        return ch - 'a';
    }
    return ch - 'A' + 26;
}

char id_to_char(int id) {
    if (id < 26) {
        return char('a' + id);
    }
    return char('A' + (id - 26));
}

void add_edge(int u, int v, int len) {
    edge_cnt++;
    to[edge_cnt] = v;
    w[edge_cnt] = len;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void dijkstra(int start) {
    for (int i = 0; i < MAXN; i++) {
        dist_arr[i] = INF;
        vis[i] = false;
    }

    priority_queue<HeapNode> pq;
    dist_arr[start] = 0;
    pq.push({start, 0});

    while (!pq.empty()) {
        HeapNode cur = pq.top();
        pq.pop();

        int u = cur.u;
        if (vis[u]) {
            continue;
        }
        vis[u] = true;

        for (int i = head[u]; i != 0; i = nxt[i]) {
            int v = to[i];
            int nd = dist_arr[u] + w[i];
            if (nd < dist_arr[v]) {
                dist_arr[v] = nd;
                pq.push({v, nd});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> p;

    for (int i = 0; i < MAXN; i++) {
        head[i] = 0;
    }
    edge_cnt = 0;

    for (int i = 1; i <= p; i++) {
        char a, b;
        int len;
        cin >> a >> b >> len;

        int u = char_to_id(a);
        int v = char_to_id(b);
        add_edge(u, v, len);
        add_edge(v, u, len);
    }

    int z_id = char_to_id('Z');
    int answer_id = -1;
    int answer_dist = INF;

    for (int i = char_to_id('A'); i < z_id; i++) {
        dijkstra(i);
        if (dist_arr[z_id] < answer_dist) {
            answer_dist = dist_arr[z_id];
            answer_id = i;
        }
    }

    cout << id_to_char(answer_id) << ' ' << answer_dist << '\n';

    return 0;
}
