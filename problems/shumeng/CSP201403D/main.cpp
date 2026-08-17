/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:51
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXV = 205;
const int MAXK = 105;
const int INF = 0x3f3f3f3f;

int n, m, k;
long long r;
long long x[MAXV], y[MAXV];
vector<int> graph[MAXV];
int dist[MAXV][MAXK];

bool can_connect(int a, int b) {
    long long dx = x[a] - x[b];
    long long dy = y[a] - y[b];
    return dx * dx + dy * dy <= r * r;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k >> r;
    int total = n + m;
    for (int i = 1; i <= total; i++) {
        cin >> x[i] >> y[i];
    }

    for (int i = 1; i <= total; i++) {
        for (int j = i + 1; j <= total; j++) {
            if (can_connect(i, j)) {
                graph[i].push_back(j);
                graph[j].push_back(i);
            }
        }
    }

    memset(dist, 0x3f, sizeof(dist));
    queue<pair<int, int> > q;
    dist[1][0] = 0;
    q.push(make_pair(1, 0));

    while (!q.empty()) {
        pair<int, int> now = q.front();
        q.pop();

        int u = now.first;
        int used = now.second;
        for (int i = 0; i < (int)graph[u].size(); i++) {
            int v = graph[u][i];
            int next_used = used + (v > n);
            if (next_used > k || dist[v][next_used] != INF) {
                continue;
            }

            dist[v][next_used] = dist[u][used] + 1;
            q.push(make_pair(v, next_used));
        }
    }

    int answer = INF;
    for (int used = 0; used <= k; used++) {
        answer = min(answer, dist[2][used]);
    }

    // 路径有 answer 条边，去掉两端路由器后剩下 answer - 1 个中转。
    cout << answer - 1 << '\n';
    return 0;
}
