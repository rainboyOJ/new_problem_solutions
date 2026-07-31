/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 21:39
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;
const int MAXV = MAXN * 2 + 5;
const int MAXE = 500000;
const long long INF = (long long)4e18;

struct Edge {
    int to, next;
    long long flow;
};

int n, m, source, sink, head[MAXV], level[MAXV], current[MAXV], edge_count = 1;
Edge edge[MAXE];

void add_edge(int from, int to, long long flow) {
    edge[++edge_count] = {to, head[from], flow};
    head[from] = edge_count;
    edge[++edge_count] = {from, head[to], 0};
    head[to] = edge_count;
}

bool bfs() {
    queue<int> q;
    memset(level, -1, sizeof(level));
    level[source] = 0;
    q.push(source);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int i = head[node]; i; i = edge[i].next) {
            if (edge[i].flow > 0 && level[edge[i].to] == -1) {
                level[edge[i].to] = level[node] + 1;
                q.push(edge[i].to);
            }
        }
    }
    return level[sink] != -1;
}

long long dfs(int node, long long limit) {
    if (node == sink) return limit;
    for (int &i = current[node]; i; i = edge[i].next) {
        int to = edge[i].to;
        if (edge[i].flow == 0 || level[to] != level[node] + 1) continue;
        long long pushed = dfs(to, min(limit, edge[i].flow));
        if (pushed) {
            edge[i].flow -= pushed;
            edge[i ^ 1].flow += pushed;
            return pushed;
        }
    }
    return 0;
}

long long dinic() {
    long long result = 0, pushed;
    while (bfs()) {
        memcpy(current, head, sizeof(head));
        while ((pushed = dfs(source, INF)) != 0) result += pushed;
    }
    return result;
}

long long get_value(int a, int b, int c, long long x) {
    return 1LL * a * x * x + 1LL * b * x + c;
}

long long get_inner_best(int left, int right, int a, int b, int c) {
    long long answer = -(long long)4e18;
    int candidates[4] = {left + 1, right - 1, left + 1, right - 1};
    if (a < 0) {
        long long denominator = -2LL * a;
        long long numerator = b;
        long long floor_value = numerator >= 0 ? numerator / denominator : -((-numerator + denominator - 1) / denominator);
        candidates[2] = (int)floor_value;
        candidates[3] = (int)(floor_value + 1);
    }
    for (int i = 0; i < 4; i++) {
        long long x = max((long long)left + 1, min((long long)right - 1, (long long)candidates[i]));
        answer = max(answer, get_value(a, b, c, x));
    }
    return answer;
}

void add_weight(int node, long long value, long long &sum) {
    if (value > 0) {
        add_edge(source, node, value);
        sum += value;
    } else if (value < 0) {
        add_edge(node, sink, -value);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    source = 2 * n + 1;
    sink = source + 1;
    long long positive_sum = 0;
    for (int i = 1; i <= n; i++) {
        int left, right, a, b, c;
        cin >> left >> right >> a >> b >> c;
        long long endpoint = max(get_value(a, b, c, left), get_value(a, b, c, right));
        long long inner = get_inner_best(left, right, a, b, c);
        add_weight(i, inner, positive_sum);
        add_weight(i + n, endpoint - inner, positive_sum);
        add_edge(i + n, i, INF);
    }
    for (int i = 1; i <= m; i++) {
        int type, x, y;
        cin >> type >> x >> y;
        if (type == 1) add_edge(y, x, INF);
        else add_edge(y + n, x, INF);
    }
    cout << positive_sum - dinic() << '\n';

    return 0;
}
