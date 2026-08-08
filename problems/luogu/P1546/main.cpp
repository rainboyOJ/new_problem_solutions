#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int INF = 1e9;

int n;
int cost[MAXN][MAXN];
int dist_to_tree[MAXN];
bool vis[MAXN];

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

        vis[u] = true;
        answer += dist_to_tree[u];

        for (int v = 1; v <= n; v++) {
            if (vis[v]) {
                continue;
            }
            if (cost[u][v] < dist_to_tree[v]) {
                dist_to_tree[v] = cost[u][v];
            }
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> cost[i][j];
        }
    }

    cout << prim() << '\n';

    return 0;
}
