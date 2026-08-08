#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2005;
const int INF = 1e9;

int n, limit_c;
int x[MAXN], y[MAXN];
int dist_to_tree[MAXN];
bool vis[MAXN];

int dis2(int i, int j) {
    int dx = x[i] - x[j];
    int dy = y[i] - y[j];
    return dx * dx + dy * dy;
}

int prim() {
    for (int i = 1; i <= n; i++) {
        dist_to_tree[i] = INF;
        vis[i] = false;
    }

    dist_to_tree[1] = 0;
    int answer = 0;

    for (int i = 1; i <= n; i++) {
        int u = 0;
        for (int j = 1; j <= n; j++) {
            if (vis[j]) {
                continue;
            }
            if (u == 0 || dist_to_tree[j] < dist_to_tree[u]) {
                u = j;
            }
        }

        if (u == 0 || dist_to_tree[u] == INF) {
            return -1;
        }

        vis[u] = true;
        answer += dist_to_tree[u];

        for (int v = 1; v <= n; v++) {
            if (vis[v]) {
                continue;
            }
            int w = dis2(u, v);
            if (w < limit_c) {
                continue;
            }
            if (w < dist_to_tree[v]) {
                dist_to_tree[v] = w;
            }
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> limit_c;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    cout << prim() << '\n';

    return 0;
}
